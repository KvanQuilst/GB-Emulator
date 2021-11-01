/*
 * gpu.c
 *
 * handles the graphics processing
 */

#include <SDL2/SDL.h>

#include "registers.h"
#include "gpu.h"

////
//	Globals
////
SDL_Window *window;
SDL_Event e;
bool running;

////
//	Prototypes
////

// print error message and exit with code 1
void g_error(const char *msg)
{
	fprintf(stderr, "gpu error: %s\n", msg);
	exit(1);
}

// process any frame rendering
void gpu_step ()
{

}

///////////////////
//
// Screen Functions
//
///////////////////

// initialize the screen
void gpu_init ()
{
	SDL_Surface *surface;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		g_error(SDL_GetError());
	}

	window = SDL_CreateWindow("gbemu",
														SDL_WINDOWPOS_CENTERED,
														SDL_WINDOWPOS_CENTERED,
														160, 144, 0);
	if (!window) {
		g_error(SDL_GetError());
	}

	surface = SDL_GetWindowSurface(window);
	if (!surface) {
		g_error(SDL_GetError());
	}

	SDL_UpdateWindowSurface(window);
}
