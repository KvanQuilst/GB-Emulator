/*
 * memory.c
 *
 * handles memory storage, access, and allocation of all vareties
 */

#include "memory.h"

uint8_t mem[0xFFFF];

void init_mem(void)
{
  /* Special I/O Setting */
  mem[0xFF05] = 0x00; // TI MA
  mem[0xFF06] = 0x00; // TMA
  mem[0xFF07] = 0x00; // TAC
  mem[0xFF10] = 0x80; // NR 10
  mem[0xFF11] = 0xBF; // NR 11
  mem[0xFF12] = 0xF3; // NR 12
  mem[0xFF14] = 0xBF; // NR 14
  mem[0xFF16] = 0x3F; // NR 21
  mem[0xFF17] = 0x00; // NR 22
  mem[0xFF19] = 0xBF; // NR 24
  mem[0xFF1A] = 0x7F; // NR 30
  mem[0xFF1B] = 0xFF; // NR 31
  mem[0xFF1C] = 0x9F; // NR 32
  mem[0xFF1E] = 0xBF; // NR 33
  mem[0xFF20] = 0xFF; // NR 41
  mem[0xFF21] = 0x00; // NR 42
  mem[0xFF22] = 0x00; // NR 43
  mem[0xFF23] = 0xBF; // NR 30
  mem[0xFF24] = 0x77; // NR 50
  mem[0xFF25] = 0xF3; // NR 51
  mem[0xFF26] = 0xF1; // NR 52
  mem[0xFF40] = 0x91; // LCDC
  mem[0xFF42] = 0x00; // SCY
  mem[0xFF43] = 0x00; // SCX
  mem[0xFF45] = 0x00; // LYC
  mem[0xFF47] = 0xFC; // BGP
  mem[0xFF48] = 0xFF; // OBP0
  mem[0xFF49] = 0xFF; // OBP1
  mem[0xFF4A] = 0x00; // WY
  mem[0xFF4B] = 0x00; // WX
  mem[0xFFFF] = 0x00; // I E
}

uint8_t read_byte(uint16_t address)
{
	/*if (address > 0xFFFF) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}*/
	return mem[address];
}

uint16_t read_double(uint16_t address)
{
	uint16_t dbl;
	if (address > 0xFFFE) {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	dbl = (uint16_t) mem[address];
  dbl += ((uint16_t) mem[address+1])<<0x08;
	return dbl;
}

uint16_t pop_stack(void)
{
	return read_double(registers.sp);
}

void write_byte(uint16_t address, uint8_t byte)
{
	//TODO CATCH ERROR IF invalid address to write

	/*if (address > 0xFFFF) {
		fprintf(stderr, "write_byte: invalid address\n");
		exit(1);
	}*/
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

void push_stack(uint16_t dbl)
{
	write_double(registers.sp, dbl);
}
