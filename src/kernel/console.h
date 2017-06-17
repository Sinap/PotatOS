#ifndef _POTATOS_KERNEL_CONSOLE_H_
#define _POTATOS_KERNEL_CONSOLE_H_
#ifndef POTATOS_KERNEL
#error "NOOOOO!"
#endif

#include <inc/types.h>

#define MONO_BASE   0x3b4
#define MONO_BUFF   0xb0000
#define CGA_BASE    0x3d4
#define CGA_BUFF    0xb8000

// 80x25 screen. wow!
#define CRT_ROWS    25
#define CRT_COLS    80
#define CRT_SIZE    (CRT_ROWS * CRT_COLS)

/**
 * [console_init description]
 */
void console_init(void);

/**
 * [console_getc description]
 * @return  [description]
 */
int console_getc(void);

/**
 * Keyboard interrupt
 * IRQ 1
 */
void kbd_intr(void);

/**
 * Serial interrupt
 * IRQ 4
 */
void serial_intr(void);

#endif  // !_POTATOS_KERNEL_CONSOLE_H_
