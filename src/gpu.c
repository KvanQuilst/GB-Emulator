/*
 * gpu.c
 *
 * handles the graphics processing
 */

#include <SDL2/SDL.h>

#include "gpu.h"
#include "memory.h"

/*struct tile
{
  uint8_t tile[8][8];
};*/

////
//	Globals
////
SDL_Window *window;
SDL_Surface *surface;
SDL_Event e;

uint8_t pixels[HEIGHT*WIDTH] = {0};

// print error message and exit with code 1
static void g_error(const char *msg)
{
	fprintf(stderr, "gpu error: %s\n", msg);
	exit(1);
}

// process any frame rendering
void gpu_step(void)
{
  g_error("no");
}

// initialize gpu data
void gpu_init(void)
{
  uint8_t lcdc = read_byte(LCDC);
  uint16_t addr = (lcdc & 0x04) ? 0x9C00 : 0x9800;
  int i, j;

}
