/*
 * gpu.h
 *
 */

#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#define HEIGHT 256
#define WIDTH 256
#define TILE_NUM 384

extern bool running;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void gpu_init(void);
void gpu_step(void);
