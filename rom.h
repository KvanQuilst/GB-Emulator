/*
 * rom.h
 *
 * handles the rom loading and processing through the rom header,
 * printing to the console the rom header info
 */

// Locations on ROM for specific data
#define ROM_TITLE	0x0134
#define ROM_TYPE	0x0147
#define ROM_SIZE	0x0148
#define RAM_SIZE	0x0149
#define ROM_START	0x0150  

// constants
#define TITLE_SIZE 16

// ROM types
// S - RUMBLE
// T - TIMER
// R - RAM
// B - BATTERY
enum rom_t {
	ROM		= 0x00,
	MBC1	= 0x01,
	MBC1_R	= 0x02,
	MBC1_RB	= 0x03,
	MBC2	= 0x05,
	MBC2_B	= 0x06,
	ROM_R	= 0x08,
	ROM_RB	= 0x09,
	MMM01	= 0x0B,
	MMM01_R	= 0x0C,
	MMM01_RB= 0x0D,
	MBC3_TB	= 0x0F,
	MBC3_TRB= 0x10,
	MBC3	= 0x11,
	MBC3_R	= 0x12,
	MBC3_RB = 0x13,
	MBC4	= 0x15,
	MBC4_R	= 0x16,
	MBC4_RB	= 0x17,
	MBC5	= 0x19,
	MBC5_R	= 0x1A,
	MBC5_RB	= 0x1B,
	MBC5_S	= 0x1C,
	MBC5_SR	= 0x1D,
	MBC5_SRB= 0x1E,
	POKECAM	= 0xFC,
	BANDAI	= 0xFD, // TAMA5 designed for tamagatchi
	HuC3	= 0xFE,
	HuC3_RB	= 0xFF
};

// prints header info and loads rom content into cart
// requires: filename of GB rom
// returns: 0 on success, -1 on fail
uint8_t loadROM(char *filename);
