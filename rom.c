/*
 * rom.c
 *
 * handles the rom loading and processing through the rom header, 
 * printing to the console the rom header info
 */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "rom.h"

const char *rom_string[256] = 
{
	[ROM]		= "ROM",
	[MBC1]		= "MBC1",
	[MBC1_R]	= "MBC1+RAM",
	[MBC1_RB]	= "MBC1+RAM+BATT",
	[MBC2]		= "MBC2",
	[MBC2_B]	= "MBC2_BATT",
	[ROM_R]		= "ROM+RAM",
	[ROM_RB]	= "ROM+RAM+BATT",
	[MMM01]		= "MMM01",
	[MMM01_R]	= "MMM01+RAM",
	[MMM01_RB]	= "MMM01+RAM+BATT",
	[MBC3_TB]	= "MBC3+TIMER+BATT",
	[MBC3_TRB]	= "MBC3+TIMER+RAM+BATT",
	[MBC3]		= "MBC3",
	[MBC3_R]	= "MBC3+RAM",
	[MBC3_RB]	= "MBC3+RAM+BATT",
	[MBC4]		= "MBC4",
	[MBC4_R]	= "MBC4+RAM",
	[MBC4_RB]	= "MBC4+RAM+BATT",
	[MBC5]		= "MBC5",
	[MBC5_R]	= "MBC5+RAM",
	[MBC5_RB]	= "MBC5+RAM+BATT",
	[MBC5_S]	= "MBC5+RUMBLE",
	[MBC5_SR]	= "MBC5+RUMBLE+RAM",
	[MBC5_SRB]	= "MBC5+rUMBLE+RAM+BATT",
	[POKECAM]	= "Pocket Camera",
	[BANDAI]	= "Bandai TAMA5",
	[HuC3]		= "Hudson HuC3",
	[HuC3_RB]	= "Hudson HuC3+RAM+BATT"
};

uint8_t loadROM(char* filename)
{
	char header[ROM_START]; // header of the rom
	char title[TITLE_SIZE];	// title of rom
	enum rom_t rom_type;	// type of ram
	int rom_size;			// size of the rom
	int ram_size;			// size of the save ram
	size_t length;			// size of file

	FILE *rom;

	// open the file
	if ((rom = fopen(filename, "r")) == NULL) {
		perror("fopen");
		return -1;
	}

	// Determine size of file

		// seek to end of file
	if (fseek(rom, 0, SEEK_END) == -1) {
		perror("fseek");
		fclose(rom);
		return -1;
	}
	
		// retrieve offset of end of file
	if ((length = ftell(rom)) == -1) {
		perror("ftell");
		fclose(rom);
		return -1;
	}

		// check file length
	if (length < ROM_START) {
		fprintf(stderr, "file is too small!\n");
		fclose(rom);
		return -1;
	}

	rewind(rom);

	// read header into string
	length = 0;
	memset(title, 0, ROM_START);
	while (length < ROM_START) {
		errno = 0;		
		length += fread(header, 1, ROM_START, rom);
		if (errno != 0) {
			perror("fread");
			fclose(rom);
			return -1;
		}
	}

	memcpy(title, &header[ROM_TITLE], TITLE_SIZE);
	printf("Title:		%s\n", title);

	rom_type = header[ROM_TYPE];
	printf("ROM Type:	%s\n", rom_string[rom_type]);

	rom_size = 2<<(header[ROM_SIZE]+4);
	printf("ROM Size:	%ukB\n", rom_size);

	ram_size = (header[RAM_SIZE]>0) * 2<<((header[RAM_SIZE]*2)-1);
	printf("RAM Size:	%ukB\n", ram_size);

	return 0;
}
