#ifndef TERM_INCLUDED
#define TERM_INCLUDED

#include <stdint.h>
#include <stddef.h>

static const size_t VGA_HEIGHT = 25;
static const size_t VGA_WIDTH = 80;

/* Hardware text mode color constants. */
enum vga_color {
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

/* Create and return color code from foreground
 * and background color constants in the form of
 *    bg   fg
 * 0b____|____
 */
uint8_t make_color(enum vga_color fg, enum vga_color bg);

/* Makes an entry in the terminal_buffer of character and assosciated color in the form of
 *	   color    char 
 * 0b________|________
 *    8 bits   8 bits
 */
uint16_t make_vgaentry(char c, uint8_t color);

/* Initialize the terminal
 * Clears every entry in the buffer and sets the position 
 * start in upper left, with a light grey foreground and
 * black background. `terminal_buffer` is set to point at
 * 0xB8000
 */
void terminal_initialize();

/* Sets the terminal colors
 * `color` input is color code in the form returned by
 * `make_color`.
 */
void terminal_setcolor(uint8_t color);

// Sets cursor position in the terminal
void terminal_set_cursor(size_t x, size_t y);

/* Scrolls the terminal down 1 line, clearing the bottom
 * line for further input
 */
void terminal_scroll();

/* Creates a new entry in the terminal of provided character
 * and color, at provided position.
 */
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

/* Writes character into terminal, using color and position set by the global
 * constants. Contains logic to move position forward and handle special
 * characters such as newlines, tabs and backspace.
 */
void terminal_putchar(char c);

// Writes string of characters into terminal
void terminal_writestring(const char* data);

// Returns length of input string
size_t strlen(const char* str);

#endif // TERM_INCLUDED
