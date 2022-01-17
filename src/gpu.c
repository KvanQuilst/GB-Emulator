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
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Event e;

uint8_t pixels[HEIGHT*WIDTH*4];

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
  int i, offset;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    g_error("SDL did not intialize!");
  }
  atexit(SDL_Quit);

  window = SDL_CreateWindow("gbemu", 
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            HEIGHT, WIDTH, 0);
                            //160, 144, 0);
  if (!window) {
    g_error("window did not initialize!");
  }

  renderer = SDL_CreateRenderer(window,
                                -1,
                                SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    SDL_DestroyWindow(window);
    g_error("renderer did not initialize!");
  }

  texture = SDL_CreateTexture(renderer,
                              SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STREAMING,
                              WIDTH, HEIGHT);
  if (!texture) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    g_error("texture did not initialize!");
  }

  memset(pixels, 255, HEIGHT*WIDTH*4);

  // set background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  for (i = 0; i < 255; i++) {
    offset = (WIDTH * 4 * i) + i * 4;        
    pixels[offset + 0] = (uint8_t) (0xFF0000 & GREY2) >> 4;
    pixels[offset + 1] = (uint8_t) (0x00FF00 & GREY2) >> 2;
    pixels[offset + 2] = (uint8_t) (0x0000FF & GREY2);
    pixels[offset + 3] = SDL_ALPHA_OPAQUE;
  }

  SDL_UpdateTexture(texture,
                    NULL,
                    pixels,
                    WIDTH*4);

  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);

}
