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
#include "gpu.h"
#include "registers.h"
#include "rom.h"

///////////////
//
// GLOBAL VARS
//
///////////////

bool debug = false;	// debug flag

SDL_Window *window;
SDL_Surface *surface;
SDL_Event e;
bool running;

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
	fprintf(stderr, "\t-d: enable debug\n");
	fprintf(stderr, "\t-t: term only\n");
	fprintf(stderr, "\t-h: show this message\n");
	exit(1);
}

// print error message and exit with code 1
void p_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

int main(int argc, char **argv)
{
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
	while ((ch = getopt(argc, argv, "dth:")) != -1) {
		argnum++;
		switch (ch) {
			case 'd': /* debug */
				debug = true;
				break;
			case 't':	/* term only */
				nowin = true;
				break;
			case 'h': /* help */
				usage(argv[0]);
				break;
		}
	}

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
	if (debug) {
		printf("-----------------------------------------------\n\n");
		printf("loading file...\n\n");
	}

	if (loadROM(filename) == -1) p_error("error loading file");

	registers.pc = ROM_START;

	// print legend for debug info
	if (debug) printf("Instr\t\t\tOP\trF\trA\trB\trC\trD\trE\trH\trL\trSP\trPC\n");
	
///////////////////////////////////////////////////////////
//
// GPU Initialization
//
///////////////////////////////////////////////////////////

  //gpu_init();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		p_error("error\n");
	}
	atexit(SDL_Quit);

	window = SDL_CreateWindow("gbemu",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														160, 144, 0);
	if (!window) {
		p_error("error\n");
	}

	surface = SDL_GetWindowSurface(window);
	if (!surface) {
		p_error("error\n");
	}

	SDL_UpdateWindowSurface(window);

///////////////////////////////////////////////////////////
//
// Program Loop
//
///////////////////////////////////////////////////////////

	while (running) {
    if (!stopped)
		  cpu_step();

    while (!nowin && SDL_PollEvent(&e) > 0) {
      switch(e.type) {
        case SDL_QUIT:
          running = false;
          break;

        case SDL_KEYDOWN:
          uint8_t const *keys = SDL_GetKeyboardState(NULL);

          if (keys[SDL_SCANCODE_ESCAPE] == 1) running = false;
          break;
      }
	  }

	  SDL_UpdateWindowSurface(window);
	}

	return 0;
}
