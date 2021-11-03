/*
 * gpu.h
 *
 */

#pragma once

#include <stdbool.h>

extern bool running;

void gpu_init(void);
void gpu_exit(void);
void gpu_step(void);
