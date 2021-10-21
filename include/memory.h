/*
 * memory.h
 *
 * 
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "registers.h"
#include "rom.h"

struct memory {
	union {
		struct {
			uint8_t cart[0x8000];	// 32kB size ROM
			uint8_t vram[0x2000]; // video ram
			uint8_t sram[0x2000];	// switchable ram bank
			uint8_t lram[0x2000];	// low internal ram
			uint8_t elram[0x2000];// echo of low internal ram
			uint8_t oam[0xA0];		// sprites
			uint8_t blankl[0x60]; // blank mem below i/o
			uint8_t io[0x4C];			// input/output storage
			uint8_t blankh[0xBC];	// blank mem above i/o
			uint8_t hram[0x7F];		// high internal ram
		};
		uint8_t full[0xFFFF];
	};
} extern memory;


// read a byte from the memory address space
// requires: an address for reading from
// returns: the byte at the address
uint8_t read_byte(uint16_t address);

// read a double byte from the memory address space
// requires: an address for reading from
// reutrns: the double byte at the address
uint16_t read_double(uint16_t address);

// read a double byte from the stack's current pos
// returns: the value at the stack pointer
uint16_t read_stack(void);

// write a byte to the provided address
// requires: an address to write to, the byte to be written
void write_byte(uint16_t address, uint8_t byte);

// write double word to the provided address
// requires: an address to write to, the double byte to be written
void write_double(uint16_t address, uint16_t dbl);

// write a double byte value to the stack's current pos
// requires: a double byte value
void write_stack(uint16_t dbl);
