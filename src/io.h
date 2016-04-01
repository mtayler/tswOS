#ifndef IO_INCLUDED
#define IO_INCLUDED

#include <stdint.h>

/*
 * Output functions
 * Take different lengths of inputs (byte, word, or long),
 * and write them to the I/O location given by `port`
 */
void outb(uint16_t port, uint8_t val);
void outw(uint16_t port, uint16_t val);
void outl(uint16_t port, uint32_t val);

/*
 * Input functions
 * Returns input of chosen length (byte, word, or long)
 * read from the provided I/O location in `port`
 */
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

#endif // IO_INCLUDED
