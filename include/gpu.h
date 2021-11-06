/*
 * gpu.h
 *
 */

#pragma once

#include <stdbool.h>

#define TILE_NUM 384

extern bool running;
extern SDL_Window *window;
extern SDL_Surface *surface;
extern SDL_Event e;

void gpu_init(void);
void gpu_exit(void);
void gpu_step(void);
void print_tile(uint8_t tile[8][8]);
