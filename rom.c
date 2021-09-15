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

uint8_t loadROM(char* filename)
{
	char title[TITLE_SIZE];	// title of rom
	uint8_t rom_size;		// size of the rom
	uint8_t ram_size;		// size of the save ram
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

	// get title
	
		// set position
	if (fseek(rom, 0x0134, SEEK_SET) == -1) {
		perror("fseek");
		fclose(rom);
		return -1;
	}

		// read title
	length = 0;
	memset(title, 0, TITLE_SIZE);
	while (length < TITLE_SIZE) {
		errno = 0;		
		length += fread(title, 1, TITLE_SIZE, rom);
		if (errno != 0) {
			perror("fread");
			fclose(rom);
			return -1;
		}
	}

	printf("Title: %s\n", title);

	// determine rom type


	return 0;
}
