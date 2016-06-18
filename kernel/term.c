#include "term.h"
#include "io.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t make_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t make_vgaentry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_set_cursor(size_t x, size_t y) {
	uint16_t pos = y * VGA_WIDTH + x;
	// cursor LOW port to VGA INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (pos&0xFF));
	// cursor HIGH port to VGA INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (pos>>8)&0xFF);
}

void terminal_scroll() {
	for (size_t y=1; y < VGA_HEIGHT; y++) {
		for (size_t x=0; x < VGA_WIDTH; x++) {
			size_t index = y * VGA_WIDTH + x;
			size_t prev_index = (y-1) * VGA_WIDTH + x;
			terminal_buffer[prev_index] = terminal_buffer[index];
		}
	}
	for (size_t x=0; x < VGA_WIDTH; x++) {
		size_t index = (VGA_HEIGHT-1)*VGA_WIDTH + x;
		terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

void terminal_putchar(char c) {
	if (c == '\b') {
		if (terminal_column > 0)
			terminal_column--;

		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
		terminal_set_cursor(terminal_column, terminal_row);
		return;
	}
	if (c == '\t') {
		terminal_column += 4;
	}
	if (c != '\n' && c != '\t') {
		terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	}
	if (++terminal_column >= VGA_WIDTH || c == '\n') {
		terminal_column = 0;
		if (terminal_row+1 >= VGA_HEIGHT) {
			terminal_scroll();
		}
		else {
			++terminal_row;
		}
	}

	terminal_set_cursor(terminal_column, terminal_row);
}

void terminal_writestring(const char* data) {
	size_t datalen = strlen(data);
	for (size_t i = 0; i < datalen; i++)
		terminal_putchar(data[i]);
}

size_t strlen(const char* str) {
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}
