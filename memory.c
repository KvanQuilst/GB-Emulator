/*
 * memory.c
 *
 * handles memory storage, access, and allocation of all vareties
 */

#include "memory.h"

#define CART 0x0000
#define VRAM 0x8000
#define SRAM 0xA000
#define LRAM 0xC000
#define OAM  0xFE00
#define IO	 0xFF00
#define HRAM 0xFF80

uint8_t cart[0x8000];	// 32kB size ROM
uint8_t vram[0x2000]; // video ram
uint8_t sram[0x2000];	// switchable ram bank
uint8_t lram[0x2000];	// low internal ram
uint8_t oam[0xA0];		// sprites
uint8_t io[0x4C];			// input/output storage
uint8_t hram[0x7F];		// high internal ram

uint8_t read_byte(uint8_t address)
{
	//printf("read_byte\n");
	if (address >= HRAM) {
		return hram[address-HRAM];
	} else if (address >= IO) {
		return io[address-IO];
	} else if (address >= OAM) {
		return oam[address-OAM];
	} else if (address >= LRAM) {
		return lram[address-LRAM];
	} else if (address >= SRAM) {
		return sram[address-SRAM];
	} else if (address >= VRAM) {
		return vram[address-VRAM];
	} else {
		return cart[address];
	}
}
