/*
 * main.c
 *
 * central gb emulation file
 * handles screen initialization and option processing
 */

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cpu.h"
#include "global.h"
#include "registers.h"
#include "rom.h"
///////////////
//
// GLOBAL VARS
//
///////////////

bool debug = false;	// debug flag
bool printregs = false; // print regsiters table

///////////////
//
// PROTOTYPES
//
///////////////

// print a message regarding the usage of gbemu
// automatically exits program with exit code 1
void usage(char *msg)
{
	fprintf(stderr, "%s: <flags> filename\n", msg);
	fprintf(stderr, "  -d: enable debug\n");
	fprintf(stderr, "  -t: term only\n");
	fprintf(stderr, "  -r: print register table\n");
	fprintf(stderr, "  -h: show this message\n");
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
	bool running = true;	  	// is emulator running?
	bool nowin = false;				// toggle window
	char *filename;						// filename provided from user
	char ch;									// char for options
	int argnum = 1;
	
///////////////////////////////////////////////////////////
//
// Initlize and Arguments
//
///////////////////////////////////////////////////////////

	// arg checking
	while ((ch = getopt(argc, argv, "dtrh:")) != -1) {
		argnum++;
		switch (ch) {
			case 'd': /* debug */
				debug = true;
				break;
			case 't':	/* term only */
				nowin = true;
				break;
			case 'r': /* print regs */
				printregs = true;
				break;
			case 'h': /* help */
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

/////////////////////////////////////////////////////////
//
// Rom Prep and Loading
//
/////////////////////////////////////////////////////////

	initRegs();

	// load rom
	printf("-----------------------------------------------\n\n");
	printf("loading file...\n\n");
	if (loadROM(filename) == -1) p_error("error loading file");

	registers.pc = ROM_START;

	// print legend for registers
	if (printregs) {
		printf("Instr\t\t\t| rF\trA\trB\trC\trD\trE\trH\trL\trSP\trPC\n");
	}

///////////////////////////////////////////////////////////
//
// Program Loop
//
///////////////////////////////////////////////////////////

	while (true) {
		
		cpu_step();
	}

	if (!nowin) {
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

					case SDL_KEYDOWN:
						uint8_t const *keys = SDL_GetKeyboardState(NULL);

						// exit program
						if (keys[SDL_SCANCODE_ESCAPE]) running = false;

						break;
				}
			}
			SDL_UpdateWindowSurface(window);
		}
		SDL_Quit();
	}
	
	return 0;
}

/////////////////////////////////////////////////////////
//
// Screen Functions
//
/////////////////////////////////////////////////////////

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
