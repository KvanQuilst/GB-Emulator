/*
 * memory.h
 *
 * 
 */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "rom.h"

extern uint8_t cart[0x8000];	// 32kB size ROM
extern uint8_t vram[0x2000];
extern uint8_t sram[0x2000];	// switchable ram bank
extern uint8_t lram[0x2000];	// low internal ram
extern uint8_t oam[0xA0];		// sprites
extern uint8_t io[0x4C];
extern uint8_t hram[0x7F];		// high internal ram

// read a byte from the memory address space
// requires: an address for reading from
// returns: the byte at the address
uint8_t read_byte(uint16_t address);

// read a double byte from the memory address space
// requires: an address for reading from
// reutrns: the double byte at the address
uint16_t read_double(uint16_t address);

// write a byte to the provided address
// requires: an address to write to, the byte to be written
void write_byte(uint16_t address, uint8_t byte);

// write double word to the provided address
// requires: an address to write to, the double byte to be written
void write_double(uint16_t address, uint16_t dbl);
