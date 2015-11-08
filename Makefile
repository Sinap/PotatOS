#
# Makefile
#
#
OBJDIR := build

TOP = ./src
V =

CC      := gcc -pipe
AS      := as
AR      := ar
LD      := ld
OBJCOPY := objcopy
OBJDUMP := objdump
NM      := nm

# Native commands
NCC     := gcc $(CC_VER) -pipe
TAR     := gtar
QEMU 	:= qemu-system-i386
PERL    := perl

# try to generate a unique GDB port
GDBPORT := $(shell expr `id -u` % 5000 + 25000)
# QEMU's gdb stub command line changed in 0.11
QEMUGDB = $(shell if $(QEMU) -nographic -help | grep -q '^-gdb'; \
	then echo "-gdb tcp::$(GDBPORT)"; \
	else echo "-s -p $(GDBPORT)"; fi)

# Compiler flags
# -fno-builtin is required to avoid refs to undefined functions in the kernel.
# Only optimize to -O1 to discourage inlining, which complicates backtraces.
CFLAGS := $(CFLAGS) $(DEFS) $(LABDEFS) -O1 -fno-builtin -I$(TOP) -MD
CFLAGS += -fno-omit-frame-pointer
CFLAGS += -Wall -Wno-format -Wno-unused -Werror -gstabs -m32

# Add -fno-stack-protector if the option exists.
CFLAGS += $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)

# Common linker flags
LDFLAGS := -m elf_i386

# Linker flags for JOS user programs
ULDFLAGS := -T user/user.ld

GCC_LIB := $(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

# Lists that the */Makefrag makefile fragments will add to
OBJDIRS :=

# Make sure that 'all' is the first target
all:

# Eliminate default suffix rules
.SUFFIXES:

# Delete target files if there is an error (or make is interrupted)
.DELETE_ON_ERROR:

# make it so that no intermediate .o files are ever deleted
.PRECIOUS: %.o $(OBJDIR)/boot/%.o $(OBJDIR)/kernel/%.o \
	$(OBJDIR)/lib/%.o $(OBJDIR)/fs/%.o $(OBJDIR)/net/%.o \
	$(OBJDIR)/user/%.o

KERN_CFLAGS := $(CFLAGS) -DPOS_KERNEL -gstabs
USER_CFLAGS := $(CFLAGS) -DPOS_USER -gstabs

# Include Makefrags for subdirectories
include $(TOP)/boot/Makefrag
include $(TOP)/kernel/Makefrag

IMAGES = $(OBJDIR)/kernel/kernel.img
QEMUOPTS = -hda $(OBJDIR)/kernel/kernel.img -serial mon:stdio $(QEMUEXTRA)

.gdbinit: .gdbinit.tmpl
	sed "s/localhost:1234/localhost:$(GDBPORT)/" < $^ > $@

qemu: $(IMAGES)
	$(QEMU) $(QEMUOPTS)

qemu-nox: $(IMAGES)
	@echo "Use Ctrl-a x to exit qemu"
	$(QEMU) -nographic $(QEMUOPTS)

qemu-gdb: $(IMAGES) .gdbinit
	$(QEMU) $(QEMUOPTS) -S $(QEMUGDB)

qemu-nox-gdb: $(IMAGES) .gdbinit
	$(QEMU) -nographic $(QEMUOPTS) -S $(QEMUGDB)

print-qemu:
	@echo $(QEMU)

print-gdbport:
	@echo $(GDBPORT)

print-qemugdb:
	@echo $(QEMUGDB)

# For deleting the build
clean:
	rm -rf $(OBJDIR) .gdbinit

distclean: realclean
	rm -rf conf/gcc.mk

# This magic automatically generates makefile dependencies
# for header files included from C source files we compile,
# and keeps those dependencies up-to-date every time we recompile.
# See 'mergedep.pl' for more information.
$(OBJDIR)/.deps: $(foreach dir, $(OBJDIRS), $(wildcard $(OBJDIR)/$(dir)/*.d))
	@mkdir -p $(@D)
	@$(PERL) mergedep.pl $@ $^

-include $(OBJDIR)/.deps

always:
	@:
