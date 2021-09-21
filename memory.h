/*
 * memory.h
 *
 * 
 */

#pragma once

#include <stdint.h>

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
uint8_t read_byte(uint8_t address);
