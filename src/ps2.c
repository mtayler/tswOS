#include "io.h"
#include "ps2.h"

#define PORT (0x60)

static char scancode[0xF1] = {
/*		_0   _1   _2   _3   _4   _5   _6   _7
		_8   _9   _A   _B   _C   _D   _E   _F */
/*0*/	 0,'\x1B','1', '2', '3',  '4', '5', '6',
/*0*/	'7', '8', '9', '0', '-', '=', '\b','\t',
/*1*/	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i',
/*1*/	'o', 'p', '[', ']','\n','\x1D','a','s',
/*2*/	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
/*2*/	'\'','`','\x2A','\\','z','x', 'c', 'v',
/*3*/	'b', 'n', 'm', ',', '.', '/','\x36','\x37',
};

/*
 * PS/2 keyboard input to code.
 * Currently only returns the scancode, until special
 * key functions are decided upon
 */
char get_scancode() {
	char c = 0;
	outb(PORT, c);
	do {
		if((char)inb(PORT) != c) {
			c = (char)inb(PORT);
			if (c > 0)
				return c;
		}
	} while(1);
}

char getchar() {
	return scancode[get_scancode()];
}
