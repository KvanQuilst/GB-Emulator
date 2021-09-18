/*
 * memory.c
 *
 * handles memory storage, access, and allocation of all vareties
 */

#include "memory.h"

uint8_t cart[0x8000];	// 32kB size ROM
uint8_t vram[0x2000];
uint8_t sram[0x2000];	// switchable ram bank
uint8_t lram[0x2000];	// low internal ram
uint8_t oam[0xA0];		// sprites
uint8_t io[0x4C];
uint8_t hram[0x7F];		// high internal ram
