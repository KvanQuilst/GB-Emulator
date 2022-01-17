/*
 * gpu.h
 *
 */

#pragma once

#include <stdbool.h>

#define HEIGHT 256
#define WIDTH 256
#define TILE_NUM 384
#define GREY0 0xFFFFFF
#define GREY1 0xa8a8a8
#define GREY2 0x606060
#define GREY3 0x000000

extern bool running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Event e;

void gpu_init(void);
void gpu_step(void);
