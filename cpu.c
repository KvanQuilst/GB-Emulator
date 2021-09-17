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
    {"LD (BC),A", 0, undefined, 2},		// 0x02
    {"INC BC", 0, inc_bc, 2},			// 0x03
    {"INC B", 0, inc_b, 1},				// 0x04
    {"DEC B", 0, dec_b, 1},				// 0x05
    {"LD B,0x%02x", 1, ld_b_n, 2},		// 0x06
    {"RLCA", 0, undefined, 1},          // 0x07
    {"LD (0x%04x),SP", 2, undefined, 5},// 0x08
    {"ADD HL,BC", 0, undefined, 2},     // 0x09
    {"LD A,(BC)", 0, undefined, 2},     // 0x0A
    {"DEC BC", 0, dec_bc, 2},			// 0x0B
    {"INC C", 0, inc_c, 1},				// 0x0C
    {"DEC C", 0, dec_c, 1},				// 0x0D
    {"LD C,0x%02x", 1, ld_c_n, 2},		// 0x0E
    {"RRCA", 0, undefined, 1},          // 0x0F
    {"STOP 0x%02x", 1, undefined, 1},   // 0x10
    {"LD DE,0x%04x", 2, undefined, 3},  // 0x11
    {"LD (DE),A", 0, undefined, 2},     // 0x12
    {"INC DE", 0, inc_de, 2},	        // 0x13
    {"INC D", 0, inc_d, 1},				// 0x14
    {"DEC D", 0, dec_d, 1},				// 0x15
    {"LD D,0x%02x", 1, ld_d_n, 2},		// 0x16
    {"nop", 0, undefined, 1},			// 0X17
    {"nop", 0, undefined, 3},			// 0x18
    {"nop", 0, undefined, 2},			// 0x19
    {"nop", 0, undefined, 2},			// 0x1A
    {"DEC DE", 0, dec_de, 2},			// 0x1B
    {"INC E", 0, inc_e, 1},				// 0x1C
    {"DEC E", 0, dec_e, 1},				// 0x1D
    {"LD E,0x%02x", 1, ld_e_n, 2},		// 0x1E
    {"nop", 0, undefined, 1},			// 0x1F
    {"nop", 0, undefined, 3},			// 0x20 timing is 2 or 3
    {"nop", 0, undefined, 1},			// 0x21
    {"nop", 0, undefined, 1},			// 0X22
    {"INC HL", 0, inc_hl, 2},			// 0x23
    {"INC H", 0, inc_h, 1},				// 0x24
    {"DEC H", 0, dec_h, 1},				// 0x25
    {"LD H,0x%02x", 1, ld_h_n, 2},		// 0x26
    {"nop", 0, undefined, 1},			// 0x27
    {"nop", 0, undefined, 1},			// 0x28
    {"nop", 0, undefined, 1},			// 0x29
    {"nop", 0, undefined, 1},			// 0x2A
    {"DEC HL", 0, dec_hl, 2},			// 0x2B
    {"INC L", 0, inc_l, 1},				// 0x2C
    {"DEC L", 0, dec_l, 1},				// 0x2D
    {"LD L,0x%02x", 1, ld_l_n, 2},      // 0x2E
    {"nop", 0, undefined, 1},           // 0x2F
    {"nop", 0, undefined, 1},           // 0x30
    {"nop", 0, undefined, 1},           // 0x31
    {"nop", 0, undefined, 1},			// 0x32
    {"INC SP", 0, inc_sp, 2},			// 0x33
    {"INC (HL)", 0, undefined, 3},		// 0x34
    {"DEC (HL)", 0, undefined, 3},		// 0x35
    {"nop", 0, undefined, 1},			// 0x36
    {"nop", 0, undefined, 1},			// 0x37
    {"nop", 0, undefined, 1},			// 0x38
    {"nop", 0, undefined, 1},			// 0x39
    {"nop", 0, undefined, 1},			// 0x3A
    {"DEC SP", 0, dec_sp, 2},			// 0x3B
    {"INC A", 0, inc_a, 1},				// 0x3C
    {"DEC A", 0, dec_a, 1},				// 0x3D
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
//	A
////

// INC A
void inc_a(void)
{
	registers.a++;
	registers.f |= (registers.a == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC A
void dec_a(void)
{
	registers.a--;
	registers.f |= (registers.a == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}


////
//  B
///

// INC B
void inc_b(void) 
{
	registers.b++;
	registers.f |= (registers.b == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG;
	//TODO HALF_FLAG
}

// DEC B
void dec_b(void)
{
	registers.b--;
	registers.f |= (registers.b == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD B,n
void ld_b_n(uint8_t operand) { registers.b = operand; }


////
//  C
////

// INC C
void inc_c(void)
{
	registers.c++;
	registers.f |= (registers.c == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC C
void dec_c(void)
{
	registers.c--;
	registers.f |= (registers.c == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD C,n
void ld_c_n(uint8_t operand) { registers.c = operand; }


////
//	BC
////

// INC BC
void inc_bc(void) { registers.bc++; }

// DEC BC
void dec_bc(void) {	registers.bc--; }


////
//  D
////

// INC D
void inc_d(void)
{
	registers.d++;
	registers.f |= (registers.d == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC D
void dec_d(void)
{
	registers.d--;
	registers.f |= (registers.d == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD D,n
void ld_d_n(uint8_t operand) { registers.d = operand; }


////
//  E
////

// INC E
void inc_e(void)
{
	registers.e++;
	registers.f |= (registers.e == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC E
void dec_e(void)
{
	registers.e--;
	registers.f |= (registers.e == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD E,n
void ld_e_n(uint8_t operand) { registers.e = operand; }


////
//	DE
////

// INC DE
void inc_de(void) {	registers.de++; }

// DEC DE
void dec_de(void) {	registers.de--; }


////
//  H
////

// INC H
void inc_h(void)
{
	registers.h++;
	registers.f |= (registers.h == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC H
void dec_h(void)
{
	registers.h--;
	registers.f |= (registers.h == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD H,n
void ld_h_n(uint8_t operand) { registers.h = operand; }


////
//  L
////

// INC L
void inc_l(void)
{
	registers.l++;
	registers.f |= (registers.l == 0) * ZERO_FLAG;
	registers.f &= !SUB_FLAG
	//TODO HALF_FLAG
}

// DEC L
void dec_l(void)
{
	registers.l--;
	registers.f |= (registers.l == 0) * ZERO_FLAG
				+  SUB_FLAG;
	//TODO HALF_FLAG
}

// LD L,n
void ld_l_n(uint8_t operand) { registers.l = operand; }


////
//	HL
////

// INC HL
void inc_hl(void) {	registers.hl++; }

// DEC HL
void dec_hl(void) {	registers.hl--; }
