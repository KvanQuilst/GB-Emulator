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

uint8_t read_byte(uint16_t address)
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
	} else if (address >= CART) {
		return cart[address];
	} else {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
}

uint16_t read_double(uint16_t address)
{
	uint16_t dbl;
	//printf("read_double\n");
	if (address >= HRAM) {
		dbl = ((uint16_t) hram[address-HRAM])<<0x08;
		dbl += (uint16_t) hram[address-HRAM+0x08];
	} else if (address >= IO) {
		dbl = ((uint16_t) io[address-IO])<<0x08;
		dbl += (uint16_t) io[address-IO+0x08];
	} else if (address >= OAM) {
		dbl = ((uint16_t) oam[address-OAM])<<0x08;
		dbl += (uint16_t) oam[address-OAM];
	} else if (address >= LRAM) {
		dbl = ((uint16_t) lram[address-LRAM])<<0x08;
		dbl += (uint16_t) lram[address-LRAM+0x08];
	} else if (address >= SRAM) {
		dbl = ((uint16_t) sram[address-SRAM])<<0x08;
		dbl += (uint16_t) sram[address-SRAM+0x08];
	} else if (address >= VRAM) {
		dbl = ((uint16_t) vram[address-VRAM])<<0x08;
		dbl += (uint16_t) vram[address-VRAM+0x08];
	} else if (address >= CART) {
		dbl = ((uint16_t) cart[address])<<0x08;
		dbl += (uint16_t) cart[address];
	} else {
		fprintf(stderr, "read_byte: invalid address\n");
		exit(1);
	}
	return dbl;
}

void write_byte(uint16_t address, uint8_t byte)
{
	//printf("write_byte\n");
	if (address >= HRAM) {
		hram[address-HRAM] = byte;
	} else if (address >= IO) {
		io[address-IO] = byte;
	} else if (address >= OAM) {
		oam[address-OAM] = byte;
	} else if (address >= LRAM) {
		lram[address-LRAM] = byte;
	} else if (address >= SRAM) {
		sram[address-SRAM] = byte;
	} else if (address >= VRAM) {
		vram[address-VRAM] = byte;
	} else {
		fprintf(stderr, "write_byte: invalid address\n");
		exit(1);
	}
}

void write_double(uint16_t address, uint16_t dbl)
{
	uint8_t ls = 0x00FF | dbl;
	uint8_t ms = 0xFF00 | dbl;
	//printf("write_double\n");
	if (address >= HRAM) {
		hram[address-HRAM] = ls;
		hram[address-HRAM+0x08] = ms;
	} else if (address >= IO) {
		io[address-IO] = ls;
		io[address-IO+0x08] = ms;
	} else if (address >= OAM) {
		oam[address-OAM] = ls;
		oam[address-OAM+0x08] = ms;
	} else if (address >= LRAM) {
		lram[address-LRAM] = ls;
		lram[address-LRAM+0x08] = ms;
	} else if (address >= SRAM) {
		sram[address-SRAM] = ls;
		sram[address-SRAM+0x08] = ms;
	} else if (address >= VRAM) {
		vram[address-VRAM] = ls;
		vram[address-VRAM+0x08] = ms;
	} else {
		fprintf(stderr, "write_byte: invalid address\n");
		exit(1);
	}
}
