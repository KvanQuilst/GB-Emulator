/*
 * main.c
 *
 * central gb emulation file
 * handles screen initialization and option processing
 */

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpu.h"
#include "registers.h"
#include "rom.h"

///////////////
//
// GLOBAL VARS
//
///////////////

int debug = 0;		// debug flag --> show instruction and register info

///////////////
//
// PROTOTYPES
//
///////////////

// print a message regarding the usage of gbemu
// automatically exits program with exit code 1
void usage(char *msg)
{
	fprintf(stderr, "%s: [-d] filename\n", msg);
	exit(1);
}

// print error message and exit with code 1
void p_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

SDL_Window *init_screen(void);

int main(int argc, char **argv)
{
	SDL_Window *window;	// program window
	SDL_Event e;							// tracks events from window
	bool running;							// is emulator running?
	char *filename;						// filename provided from user
	char ch;									// char for options
	int argnum = 1;

	// arg checking
	while ((ch = getopt(argc, argv, "dh:")) != -1) {
		argnum++;
		switch (ch) {
			case 'd': /* debug */
				debug = 1;
				break;
			case 'h':
				usage(argv[0]);
				break;
		}
	}

	// debug check
	if (debug) printf("debug enabled\n");

	// check for filename and set filename
	if (argnum >= argc) {
		usage(argv[0]);
	}
	filename = argv[argnum];

	// load rom
	printf("loading file...\n\n");
	if (loadROM(filename) == -1) p_error("error loading file");

	registers.pc = ROM_START;

	while (registers.pc < ROM_START + 100) {
		
		cpu_step();

	}

	window = init_screen();

	SDL_UpdateWindowSurface(window);

	// main loop
	while(running) {

		// event loop
		while (SDL_PollEvent(&e) > 0) {
			switch(e.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}
		SDL_UpdateWindowSurface(window);
	}

	return 0;
}

// initialize screen
SDL_Window *init_screen(void)
{
	SDL_Window *window;
	SDL_Surface *win_surface;
	int scrw, scrh;								// screen dimensions for windows

	// decide screen dimensions
	if (debug) {
		// screen dimensions for debug output
		scrw = 480;
		scrh = 422;
	} else {
		// default gameboy screen dimensions
		scrw = 160;
		scrh = 144;
	}

	// init window
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "SDL2 err: %s\n", SDL_GetError());
		p_error("failed to initialize SDL2 lib");
	}

	// open window
	window = SDL_CreateWindow("gbemu",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														scrw, scrh,	0);
	if (!window) {
		fprintf(stderr, "SDL2 err: %s\n", SDL_GetError());
		p_error("failed to init window");
	}

	// grab window surface
	win_surface = SDL_GetWindowSurface(window);
	if (!win_surface) {
		fprintf(stderr, "SDL2 err: %s\n", SDL_GetError());
		p_error("failed to grab window surface");
	}

	return window;
}
