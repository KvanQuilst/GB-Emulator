/*
 * cpu.h
 *
 * handles the instruction processing
 *
 */

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

extern bool stoped;

uint8_t cpu_step(void);
