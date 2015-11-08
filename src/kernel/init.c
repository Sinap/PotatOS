
// this is called by boot/main.c
// after bootload has finished we start here
void i386_init(void) {
    extern char edata[], end[];

    // Before doing anything else, complete the ELF loading process.
    // Clear the uninitialized global data (BSS) section of our program.
    // This ensures that all static/global variables start out zero.
    memset(edata, 0, end - edata);
}

/**
 * Variable panicstr contains argument to first call to panic; used as flag
 * to indicate that the kernel has already called panic.
 */
static const char *panicstr;

/**
 * Panic is called on unresolvable fatal errors.
 * It prints "panic: mesg", and then enters the kernel monitor.
 */
/*void _panic(const char *file, int line, const char *fmt, ...) {
    va_list ap;

    if (panicstr) {
        goto dead;
    }

    // be extra sure that the machine is in a reasonable state
    __asm __volatile("cli; cld");

    va_start(ap, fmt);
    cprintf("kernel panic at %s:%d: ", file, line);
    vcprintf(fmt, ap);
    cprintf("\n");
    va_end(ap);

    dead:
        // break into the kernel monitor
        while (1) {
            monitor(NULL);
        }
}

void _warn(const char *file, int line, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    cprintf("kernel warning at %s:%d: ", file, line);
    vcprintf(fmt, ap);
    cprintf("\n");
    va_end(ap);
}
*/
