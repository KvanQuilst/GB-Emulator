/*
 * memory.h
 *
 * 
 */

#pragma once

#include <stdint.h>

#include "rom.h"

extern uint8_t cart[0x8000-ROM_START]; // 32kB size ROM - header
