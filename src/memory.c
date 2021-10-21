/*
 * memory.c
 *
 * handles memory storage, access, and allocation of all vareties
 */

#include "memory.h"

// Memory boundaries
#define CART 0x0000
#define VRAM 0x8000
#define SRAM 0xA000
#define LRAM 0xC000
#define OAM  0xFE00
#define IO	 0xFF00
#define HRAM 0xFF80

// Register and device locations

struct memory memory;

uint8_t read_byte(uint16_t address)
{
	if (address > 0xFFFF) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	return memory.full[address];
}

uint16_t read_double(uint16_t address)
{
	uint16_t dbl;
	if (address > 0xFFFE) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	dbl = ((uint16_t) memory.full[address])<<0x08;
	dbl += (uint16_t) memory.full[address+1];
	return dbl;
}

uint16_t read_stack(void)
{
	return read_double(registers.sp);
}

void write_byte(uint16_t address, uint8_t byte)
{
	//TODO CATCH ERROR IF invalid address to write

	if (address > 0xFFFF) {
		fprintf(stderr, "write_byte: invalid address\n");
		exit(1);
	}
	memory.full[address] = byte;
}

void write_double(uint16_t address, uint16_t dbl)
{
	//TODO Catch error if invalid address to write

	uint8_t ls = (uint8_t) 0x00FF & dbl;
	uint8_t ms = (uint8_t) (0xFF00 & dbl)>>8;
	if (address > 0xFFFE) {
		fprintf(stderr, "write_byte: invalid address\n");
		exit(1);
	}
	memory.full[address] = ls;
	memory.full[address+1] = ms;
}

void write_stack(uint16_t dbl)
{
	write_double(registers.sp, dbl);
}
