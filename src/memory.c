/*
 * memory.c
 *
 * handles memory storage, access, and allocation of all vareties
 */

#include "memory.h"

uint8_t mem[0xFFFF];

uint8_t read_byte(uint16_t address)
{
	if (address > 0xFFFF) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	return mem[address];
}

uint16_t read_double(uint16_t address)
{
	uint16_t dbl;
	if (address > 0xFFFE) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	dbl = ((uint16_t) mem[address])<<0x08;
	dbl += (uint16_t) mem[address+1];
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
	mem[address] = byte;
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
	mem[address] = ls;
	mem[address+1] = ms;
}

void write_stack(uint16_t dbl)
{
	write_double(registers.sp, dbl);
}
