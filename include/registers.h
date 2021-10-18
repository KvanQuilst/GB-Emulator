/*
 * registers.h
 * 
 * struct representation of gb registers, compatible with register
 * pairing, allowing for 16-bit registers
 * 
 * registers a-l are all 8bit registers; the stack pointer
 * and program counter are 16bit
 * 
 * Note: Individual registers are reversed because it is
 * (assumingly) running on a little-endian machine
 * 
 *   -----------
 *  |  A  |  F  | <--- F is indirectly accessible; 
 *  |-----------|	   stores results of various math 
 *  |  B  |  C  |	   ops as well as op flags
 *  |-----------|
 *  |  D  |  E  |
 *  |-----------|
 *  |  H  |  L  |
 *  |-----------|
 *  |     SP    | <-- Stack Pointer (16bit)
 *  |-----------|
 *  |     PC    | <-- Program Counter (16bit)
 *   -----------
 */
#pragma once

#include <stdint.h>
#include <stdio.h>

#define ZERO_FLAG   0x80
#define NEG_FLAG    0x40
#define HALF_FLAG   0x20
#define CARRY_FLAG  0x10
#define ALL_FLAGS	0xF0

struct registers {
    struct {
        union {
            struct {
                uint8_t f;
                uint8_t a;
            };
            uint16_t af;
        };
    };
    struct {
        union {
            struct {
                uint8_t c;
                uint8_t b;
            };
            uint16_t bc;
        };
    };
    struct {
        union {
            struct {
                uint8_t e;
                uint8_t d;
            };
            uint16_t de;
        };
    };
    struct {
        union {
            struct {
                uint8_t l;
                uint8_t h;
            };
            uint16_t hl;
        };
    };
    uint16_t sp;
    uint16_t pc;
} extern registers;

// initialize the registers to their respective values
void initRegs(void);

// print the current state of the registers
// and the operand of the instruction
// requires: operand value, 0|1|2 bytes
void printRegs(uint16_t operands, int bytes);
