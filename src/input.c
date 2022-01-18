/*
 * input.c
 *
 * handles button inputs
 */

#include "cpu.h"
#include "gpu.h"
#include "input.h"

SDL_Event e;

void process_inputs()
{
  while (SDL_PollEvent(&e) > 0) {
    switch(e.type) {
      case SDL_QUIT:
        running = false;
        break;

      case SDL_KEYDOWN:
        uint8_t const *keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_ESCAPE] == 1) running = false;

        if (keys[SDL_SCANCODE_RETURN] == 1) stopped = false;
        break;
    }
  }
}
