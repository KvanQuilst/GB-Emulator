/*
 * rom.h
 *
 * handles the rom loading and processing through the rom header,
 * printing to the console the rom header info
 */

#include <stdint.h>
#include <stdio.h>

// prints header info and loads rom content into cart
// requires: filename of GB rom
// returns: 0 on success, 1 on fail
uint8_t loadROM(char *filename);
