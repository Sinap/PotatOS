#ifndef _POTATOS_INC_MMU_H_
#define _POTATOS_INC_MMU_H_

/**
 * This file contains definitions for the x86 memory management unit (MMU),
 * including paging- and segmentation-related data structures and constants,
 * the %cr0, %cr4, and %eflags registers, and traps.
 */

/**
 *
 *  Part 1.  Paging data structures and constants.
 *
 */

/**
 * A linear address 'la' has a three-part structure as follows:
 *
 * +--------10------+-------10-------+---------12----------+
 * | Page Directory |   Page Table   | Offset within Page  |
 * |      Index     |      Index     |                     |
 * +----------------+----------------+---------------------+
 *  \--- PDX(la) --/ \--- PTX(la) --/ \---- PGOFF(la) ----/
 *   \---------- VPN(la) ----------/
 *
 * The PDX, PTX, PGOFF, and VPN macros decompose linear addresses as shown.
 * To construct a linear address la from PDX(la), PTX(la), and PGOFF(la),
 * use PGADDR(PDX(la), PTX(la), PGOFF(la)).
 */


/**
 *
 *  Part 2.  Segmentation data structures and constants.
 *
 */

#ifdef __ASSEMBLER__

/**
 * Macros to build GDT entries in assembly.
 */
#define SEG_NULL \
    .word 0, 0; \
    .byte 0, 0, 0, 0

#define SEG(type, base, lim) \
    .word (((lim) >> 12) & 0xffff), ((base) & 0xffff); \
    .byte (((base) >> 16) & 0xff), (0x90 | (type)), \
        (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#else   // not __ASSEMBLER__

#endif  // !__ASSEMBLER__

// application segment type bits
#define STA_X 0x8 // Executable segment
#define STA_E 0x4 // Expand down (non-executable segments)
#define STA_C 0x4 // Conforming code segment (executable only)
#define STA_W 0x2 // Writeable (non-executable segments)
#define STA_R 0x2 // Readable (executable segments)
#define STA_A 0x1 // Accessed

// system segment type bits
#define STS_T16A 0x1 // available 16-bit TSS
#define STS_LDT  0x2 // Local Descriptor Table
#define STS_T16B 0x3 // busy 16-bit TSS
#define STS_CG16 0x4 // 16-bit Call Gate
#define STS_TG   0x5 // Task Gate
#define STS_IG16 0x6 // 16-bit Interrupt Gate
#define STS_TG16 0x7 // 16-bit Trap Gate
#define STS_T32A 0x9 // available 32-bit TSS
#define STS_T32B 0xb // busy 32-bit TSS
#define STS_CG32 0xc // 32-bit Call Gate
#define STS_IG32 0xe // 32-bit Interrupt Gate
#define STS_TG32 0xf // 32-bit Trap Gate

/**
 *
 *  Part 3.  Traps.
 *
 */

#endif  // !_POTATOS_INC_MMU_H_
