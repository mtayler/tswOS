#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__) || defined(__APPLE__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include "io.h"
#include "ps2.h"
#include "term.h"

#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main() {
	outb(0x60, 0);	// Clear 0x60 (PS/2) I/O register

	/* Initialize terminal interface */
	terminal_initialize();
 
	terminal_writestring("Hello, kernel World!\n");
	while (true) {
		terminal_putchar(getchar());
	}
}
