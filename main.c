/*
 * main.c
 *
 * central gb emulation file
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "registers.h"
#include "rom.h"

int main(int argc, char **argv)
{
	char *filename;		// filename provided from user

	// arg checking
	if (argc != 2) {
		fprintf(stderr, "incorrect user of gbemu\n");
		fprintf(stderr, "usage: gbemu <filename>\n");
		exit(1);
	}

	// set filename
	filename = argv[1];

	// load rom
	printf("loading file...\n\n");
	if (loadROM(filename) == -1) {
		fprintf(stderr, "error loading file\n");
		exit(1);
	}

	registers.pc = ROM_START;

	while (registers.pc < ROM_START + 50) {
		
		cpu_step();

	}
	return 0;
}
