/*
 * gpu.c * * handles the graphics processing
 */

#include "gpu.h"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

uint8_t pixels[HEIGHT*WIDTH*4];
uint8_t tiles[TILE_NUM*8*8*4];

struct palette p = {{0xFFFFFF, 0xa8a8a8, 0x606060, 0x000000}};

static void update_tiles(void);

// print error message and exit with code 1
static void g_error(const char *msg)
{
	fprintf(stderr, "gpu error: %s\n", msg);
	exit(1);
}

// initialize gpu data
void gpu_init(void)
{
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

  //memset(pixels, 255, HEIGHT*WIDTH*4);

  // set background
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  update_tiles();

  SDL_UpdateTexture(texture,
                    NULL,
                    tiles,
                    4);

  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

// process any frame rendering
void gpu_step(void)
{
  update_tiles();
}

static void update_tiles(void)
{
  uint8_t line1, line2, color;  
  uint16_t addr = 0x8000 + 0x0800 * (LCDC & 0x10);
  int i, j, k, offset;

  for (i = 0; i < TILE_NUM; i++) {
    for (j = 0; j < 8; j++) {
      line1 = read_byte(addr+j*16);
      line2 = read_byte(addr+j*16+8);
      offset = i*16 + j*2;
      for (k = 0; k < 8; k++) {
        color = (((0x80 >> k) & line1) >> (k-7)) | (((0x80 >> k) & line2) >> (k-6));
        tiles[offset] = (uint8_t) (0xFF0000 & p.colors[color]) >> 4;        
        tiles[offset+1] = (uint8_t) (0x00FF00 & p.colors[color]) >> 2;
        tiles[offset+2] = (uint8_t) (0x0000FF & p.colors[color]);
        tiles[offset+3] = SDL_ALPHA_OPAQUE;
      }
    }
  }
}
