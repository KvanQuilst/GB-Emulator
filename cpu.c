/*
 * cpu.c
 *
 * handles the instruction processing
 * 
 */

#include "registers.h"

#include "cpu.h"

void undefined(void);

// struct containing important information regarding 
// the processor instructions for GameBoy
struct instruction 
{
    char *disas;        // instruction disassembly
    uint8_t ops;        // number of operands (0-2)
    void *exec;         // function to execute instruction
    uint8_t ticks;      // machine time needed
};

const struct instruction instructions[256] =
{
    {"nop", 0, nop, 1},					// 0x00
    {"LD BC,0x%04x", 2, undefined, 3},	// 0x01 
    {"LD (BC),A", 0, undefined, 1},		// 0x02
    {"INC BC", 0, undefined, 1},		// 0x03
    {"INC B", 0, inc_b, 1},				// 0x04
    {"DEC B", 0, dec_b, 1},				// 0x05
    {"LD B,0x%02x", 1, ld_b_n, 2},		// 0x06
    {"nop", 0, undefined, 1},      // 0x07
    {"nop", 0, undefined, 1},      // 0x08
    {"nop", 0, undefined, 1},      // 0x09
    {"nop", 0, undefined, 1},      // 0x0A
    {"nop", 0, undefined, 1},      // 0x0B
    {"nop", 0, undefined, 1},      // 0x0C
    {"nop", 0, undefined, 1},      // 0x0D
    {"LD C,0x%02x", 1, ld_c_n, 2},		// 0x0E
    {"nop", 0, undefined, 1},          // 0x0F
    {"nop", 0, undefined, 1},          // 0x10
    {"nop", 0, undefined, 1},          // 0x11
    {"nop", 0, undefined, 1},          // 0x12
    {"nop", 0, undefined, 1},          // 0x13
    {"nop", 0, undefined, 1},          // 0x14
    {"nop", 0, undefined, 1},          // 0x15
    {"LD D,0x%02x", 1, ld_d_n, 2},		// 0x16
    {"nop", 0, undefined, 1},          // 0X17
    {"nop", 0, undefined, 1},          // 0x18
    {"nop", 0, undefined, 1},          // 0x19
    {"nop", 0, undefined, 1},          // 0x1A
    {"nop", 0, undefined, 1},          // 0x1B
    {"nop", 0, undefined, 1},          // 0x1C
    {"nop", 0, undefined, 1},          // 0x1D
    {"LD E,0x%02x", 1, ld_e_n, 2},		// 0x1E
    {"nop", 0, undefined, 1},          // 0x1F
    {"nop", 0, undefined, 1},          // 0x20
    {"nop", 0, undefined, 1},          // 0x21
    {"nop", 0, undefined, 1},          // 0X22
    {"nop", 0, undefined, 1},          // 0x23
    {"nop", 0, undefined, 1},          // 0x24
    {"nop", 0, undefined, 1},          // 0x25
    {"LD H,0x%02x", 1, ld_h_n, 2},		// 0x26
    {"nop", 0, undefined, 1},          // 0x27
    {"nop", 0, undefined, 1},          // 0x28
    {"nop", 0, undefined, 1},          // 0x29
    {"nop", 0, undefined, 1},          // 0x2A
    {"nop", 0, undefined, 1},          // 0x2B
    {"nop", 0, undefined, 1},          // 0x2C
    {"nop", 0, undefined, 1},          // 0x2D
    {"LD L,0x%02x", 1, ld_l_n, 2},       // 0x2E
    {"nop", 0, undefined, 1},           // 0x2F
    {"nop", 0, undefined, 1},           // 0x30
    {"nop", 0, undefined, 1},           // 0x31
    {"nop", 0, undefined, 1},			// 0x32
    {"nop", 0, undefined, 1},			// 0x33
    {"nop", 0, undefined, 1},			// 0x34
    {"nop", 0, undefined, 1},			// 0x35
    {"nop", 0, undefined, 1},			// 0x36
    {"nop", 0, undefined, 1},			// 0x37
    {"nop", 0, undefined, 1},			// 0x38
    {"nop", 0, undefined, 1},			// 0x39
    {"nop", 0, undefined, 1},			// 0x3A
    {"nop", 0, undefined, 1},			// 0x3B
    {"nop", 0, undefined, 1},			// 0x3C
    {"nop", 0, undefined, 1},			// 0x3D
    {"nop", 0, undefined, 1},			// 0x3E
    {"nop", 0, undefined, 1},			// 0x3F
    {"nop", 0, undefined, 1},			// 0x40
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
};

// for any instructions that are not defined
void undefined(void)
{
    printf("this instruction is undefined\n");
}

// nop
void nop(void) {}

////
//  B
///

// INC B
void inc_b(void) 
{
	registers.b++;
	registers.f |= (registers.b == 0) * ZERO_FLAG;
	registers.f &= (!SUB_FLAG);
	// HALF_FLAG
}

// DEC B
void dec_b(void)
{
	registers.b--;
	registers.f |= (registers.b == 0) * ZERO_FLAG
				+  SUB_FLAG;
	// HALF_FLAG
}

// LD B,n
void ld_b_n(uint8_t operand) { registers.b = operand; }


////
//  C
////

// LD C,n
void ld_c_n(uint8_t operand) { registers.c = operand; }


////
//  D
////

// LD D,n
void ld_d_n(uint8_t operand) { registers.d = operand; }


////
//  E
////

// LD E,n
void ld_e_n(uint8_t operand) { registers.e = operand; }


////
//  H
////

// LD H,n
void ld_h_n(uint8_t operand) { registers.h = operand; }


////
//  L
////

// LD L,n
void ld_l_n(uint8_t operand) { registers.l = operand; }
