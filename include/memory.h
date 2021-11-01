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

// Memory boundaries
#define CART 0x0000
#define VRAM 0x8000
#define SRAM 0xA000
#define LRAM 0xC000
#define OAM  0xFE00
#define IO	 0xFF00
#define HRAM 0xFF80

extern uint8_t mem[0xFFFF];

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
