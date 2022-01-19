/*
 * gpu.c
 *
 * handles the graphics processing
 */

#include "gpu.h"

// print error message and exit with code 1
static void g_error(const char *msg)
{
	fprintf(stderr, "gpu error: %s\n", msg);
	exit(1);
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
    pixels[offset + 0] = (uint8_t) (0xFF0000 & grey.med) >> 4;
    pixels[offset + 1] = (uint8_t) (0x00FF00 & grey.med) >> 2;
    pixels[offset + 2] = (uint8_t) (0x0000FF & grey.med);
    pixels[offset + 3] = SDL_ALPHA_OPAQUE;
  }

  SDL_UpdateTexture(texture,
                    NULL,
                    pixels,
                    WIDTH*4);

  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

static void update_tiles(void)
{
  uint8_t line1, line2;  
  uint16_t addr = 0x8000 + 0x08000 * (LCDC & 0x10);
  int i, j;

  for (i = 0; i < TILE_NUM; i++) {
    for (j = 0; j < 8; j++) {
      line1 = read_byte(addr+j*16);
      line2 = read_byte(addr+j*16+8);

      tiles[i*32+j*8] = ;
      tiles[i*32+j*8+1] = ;
      tiles[i*32+j*8+2] = ;
      tiles[i*32+j*8+3] = ;
      tiles[i*32+j*8+4] = ;
      tiles[i*32+j*8+5] = ;
      tiles[i*32+j*8+6] = ;
      tiles[i*32+j*8+7] = ;
      tiles[i*32+j*8+8] = ;
    }
  }


}

// process any frame rendering
void gpu_step(void)
{
  g_error("no");
}

