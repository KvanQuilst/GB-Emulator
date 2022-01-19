/*
 * gpu.h
 *
 */

#pragma once

#include "include.h"
#include "memory.h"
#include "palettes.h"

#define HEIGHT 256
#define WIDTH 256
#define TILE_NUM 384

extern bool running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;


SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

uint8_t pixels[HEIGHT*WIDTH*4];
uint8_t tiles[TILE_NUM*8*8];

void gpu_init(void);
void gpu_step(void);
