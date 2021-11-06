/*
 * gpu.c
 *
 * handles the graphics processing
 */

#include <SDL2/SDL.h>

#include "memory.h"
#include "registers.h"
#include "gpu.h"

/*struct tile
{
  uint8_t tile[8][8];
};*/

////
//	Globals
////

//struct tile tile_set[TILE_NUM];
uint8_t tile_set[TILE_NUM][8][8];

// print error message and exit with code 1
void g_error(const char *msg)
{
	fprintf(stderr, "gpu error: %s\n", msg);
	exit(1);
}

// process any frame rendering
void gpu_step(void)
{
	SDL_UpdateWindowSurface(window);
}

// initialize gpu data
void gpu_init(void)
{
  uint8_t *ptr;
  uint8_t offset;
  uint8_t line1, line2;
  int i, j, k;

  // TILE MAP
  ptr = &mem[VRAM + 0x0800 * (!(mem[LCDC] & 0x10))];
  
  for (i = 0; i < TILE_NUM; i++) {
    offset = i * 16;
    for (j = 0; j < 8; j++) {
      line1 = ptr[j*offset];
      line2 = ptr[j*offset+1];
      //printf("line 1: %u | line 2: %u\n", line1, line2);
      for (k = 0; k < 8; k++) {
        tile_set[i][j][k] = ((line1>>(7-k)) & 0x1)
                          + (((line2>>(7-k)) & 0x1) * 2);
      }
    }
    //print_tile (tile_set[i]);
    //printf("\n");
  }
}

// print a tile
void print_tile(uint8_t tile[8][8])
{
  int i, j;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      printf("%u", tile[i][j]);
    }
    printf("\n");
  }
}
