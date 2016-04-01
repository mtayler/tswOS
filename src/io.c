#include <stdint.h>

/*
 * Output functions
 * Take different lengths of inputs, and write them to
 * the I/O location given by `port`
 */
void outb(uint16_t port, uint8_t val) {
	asm volatile ( "outb %0, %1"
				 :
				 : "a"(val), "Nd"(port)
				 );
}

void outw(uint16_t port, uint16_t val) {
	asm volatile ( "outw %0, %1"
				 :
				 : "a"(val), "Nd"(port)
				 );
}

void outl(uint16_t port, uint32_t val) {
	asm volatile ( "outl %0, %1"
				 :
				 : "a"(val), "Nd"(port)
				 );
}

/*
 * Input functions
 * Returns input of chosen length read from the
 * provided I/O location in `port`
 */
uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile ( "inb %1, %0"
				 : "=a"(ret)
				 : "Nd"(port) );
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile ( "inw %1, %0"
				 : "=a"(ret)
				 : "Nd"(port) );
	return ret;
}

uint32_t inl(uint16_t port) {
	uint32_t ret;
	asm volatile ( "inl %1, %0"
				 : "=a"(ret)
				 : "Nd"(port) );
	return ret;
}
