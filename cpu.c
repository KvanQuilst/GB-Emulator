/*
 * cpu.c
 *
 * handles the instruction processing
 * 
 */

#include "instructions.h"
#include "registers.h"

#include "cpu.h"

// struct containing important information regarding 
// the processor instructions for GameBoy
struct instruction 
{
    char *disas;        // instruction disassembly
    uint8_t ops;        // number of operands (0-2)
    void *exec;  // function to execute instruction
    uint8_t ticks;      // machine time needed
};

const struct instruction instr[256] =
{
    {"nop", 0, nop, 1},					// 0x00
    {"LD BC,0x%04x", 2, ld_bc_nn, 3},	// 0x01 
    {"LD (BC),A", 0, undefined, 2},		// 0x02
    {"INC BC", 0, inc_bc, 2},			// 0x03
    {"INC B", 0, inc_b, 1},				// 0x04
    {"DEC B", 0, dec_b, 1},				// 0x05
    {"LD B,0x%02x", 1, ld_b_n, 2},		// 0x06
    {"RLCA", 0, undefined, 1},          // 0x07
    {"LD (0x%04x),SP", 2, undefined, 5},// 0x08
    {"ADD HL,BC", 0, add_hl_bc, 2},     // 0x09
    {"LD A,(BC)", 0, undefined, 2},     // 0x0A
    {"DEC BC", 0, dec_bc, 2},			// 0x0B
    {"INC C", 0, inc_c, 1},				// 0x0C
    {"DEC C", 0, dec_c, 1},				// 0x0D
    {"LD C,0x%02x", 1, ld_c_n, 2},		// 0x0E
    {"RRCA", 0, undefined, 1},          // 0x0F
    {"STOP 0x%02x", 1, undefined, 1},   // 0x10
    {"LD DE,0x%04x", 2, ld_de_nn, 3},	// 0x11
    {"LD (DE),A", 0, undefined, 2},     // 0x12
    {"INC DE", 0, inc_de, 2},	        // 0x13
    {"INC D", 0, inc_d, 1},				// 0x14
    {"DEC D", 0, dec_d, 1},				// 0x15
    {"LD D,0x%02x", 1, ld_d_n, 2},		// 0x16
    {"RLA", 0, undefined, 1},			// 0X17
    {"JR 0x%02x", 1, undefined, 3},		// 0x18
    {"ADD HL,DE", 0, undefined, 2},		// 0x19
    {"LD A,(DE)", 0, undefined, 2},		// 0x1A
    {"DEC DE", 0, dec_de, 2},			// 0x1B
    {"INC E", 0, inc_e, 1},				// 0x1C
    {"DEC E", 0, dec_e, 1},				// 0x1D
    {"LD E,0x%02x", 1, ld_e_n, 2},		// 0x1E
    {"RRA", 0, undefined, 1},			// 0x1F
    {"STOP", 0, undefined, 2},			// 0x20
    {"LD HL,0x%04x", 2, ld_hl_nn, 3},	// 0x21 timing is 2 or 3
    {"LD (HL+),A", 0, undefined, 2},	// 0X22
    {"INC HL", 0, inc_hl, 2},			// 0x23
    {"INC H", 0, inc_h, 1},				// 0x24
    {"DEC H", 0, dec_h, 1},				// 0x25
    {"LD H,0x%02x", 1, ld_h_n, 2},		// 0x26
    {"DAA", 0, undefined, 1},			// 0x27
    {"JR Z,0x%02x", 1, undefined, 3},	// 0x28 timing is 2 or 3
    {"ADD HL,HL", 0, undefined, 2},		// 0x29
    {"LD A,(HL+)", 0, undefined, 2},	// 0x2A
    {"DEC HL", 0, dec_hl, 2},			// 0x2B
    {"INC L", 0, inc_l, 1},				// 0x2C
    {"DEC L", 0, dec_l, 1},				// 0x2D
    {"LD L,0x%02x", 1, ld_l_n, 2},      // 0x2E
    {"CPL", 0, undefined, 1},           // 0x2F
    {"JR NC,0x%02x", 0, undefined, 3},  // 0x30 timing is 2 or 3
    {"LD SP,0x%04x", 2, ld_sp_nn, 3},   // 0x31
    {"LD (HL-),A", 0, undefined, 2},	// 0x32
    {"INC SP", 0, inc_sp, 2},			// 0x33
    {"INC (HL)", 0, undefined, 3},		// 0x34
    {"DEC (HL)", 0, undefined, 3},		// 0x35
    {"LD (HL),0x%02x", 0, undefined, 3},// 0x36
    {"SCF", 0, undefined, 1},			// 0x37
    {"JR C,0x%02x", 0, undefined, 3},	// 0x38 time is 2 or 3
    {"ADD HL,SP", 0, undefined, 2},		// 0x39
    {"LD A,(HL-)", 0, undefined, 2},	// 0x3A
    {"DEC SP", 0, dec_sp, 2},			// 0x3B
    {"INC A", 0, inc_a, 1},				// 0x3C
    {"DEC A", 0, dec_a, 1},				// 0x3D
    {"LD A,0x%02x", 0, undefined, 2},	// 0x3E
    {"CCF", 0, undefined, 1},			// 0x3F
    {"LD B,B", 0, nop, 1},				// 0x40
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
    {"nop", 0, undefined, 1},
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
static void undefined(void)
{
    printf("this instruction is undefined\n");
}

////
//  Generalized Instructions
////

// increase values and set flags
// requires: val to increase
// returns: increased value
static uint8_t inc(uint8_t val)
{
	registers.f &= !(SUB_FLAG + HALF_FLAG); // unset SUB_ and HALF_FLAG
	registers.f |= ((val & 0x0f) == 0x0f) * HALF_FLAG;
	val++;
	registers.f |= (val == 0) * ZERO_FLAG;
	return val;
}

// decrease values and set flags
// requires: val to decrease
// returns: decreased value
static uint8_t dec(uint8_t val)
{
	registers.f &= !(HALF_FLAG);
	registers.f |= (val & 0x0f) * HALF_FLAG;
	val--;
	registers.f |= (val == 0) * ZERO_FLAG
				+  SUB_FLAG;
	return val;
}

// add two 2byte values and set flags
// requires: values to add together
// returns: final value
static uint16_t add_nn(uint16_t val1, uint16_t val2)
{
	uint32_t result = val1 + val2;

	// clear SUB_, HALF_ and CARRY_FLAG
	registers.f &= !(SUB_FLAG + HALF_FLAG + CARRY_FLAG);
	registers.f |= (result & 0xffff0000) * CARRY_FLAG
				+  ((val1 & 0x0fff) + (val2 & 0x0fff) > 0x0fff) * HALF_FLAG;
	return (uint16_t) (result & 0xffff);
}

////
//	CPU Instructions
////

// 0x00 nop
static void nop(void) {}

////
//	A
////

// 0x3C INC A
static void inc_a(void) { registers.a = inc(registers.a); }

// 0x3D DEC A
static void dec_a(void) { registers.a = dec(registers.a); }


////
//  B
///

// 0x04 INC B
static void inc_b(void) { registers.b = inc(registers.b); }

// 0x05 DEC B
static void dec_b(void) { registers.b = dec(registers.b); }

// 0x06 LD B,n
static void ld_b_n(uint8_t operand) { registers.b = operand; }


////
//  C
////

// 0x0C INC C
static void inc_c(void) { registers.c = inc(registers.c); }

// 0x0D DEC C
static void dec_c(void) { registers.c = dec(registers.c); }

// 0x0E LD C,n
static void ld_c_n(uint8_t operand) { registers.c = operand; }


////
//	BC
////

// 0x02 LD BC,nn
static void ld_bc_nn(uint16_t operand) { registers.bc = operand; }

// 0x03 INC BC
static void inc_bc(void) { registers.bc++; }

// 0x0B DEC BC
static void dec_bc(void) {	registers.bc--; }


////
//  D
////

// 0x14 INC D
static void inc_d(void) { registers.d = inc(registers.d); }

// 0x15 DEC D
static void dec_d(void) { registers.d = dec(registers.d); }

// 0x16 LD D,n
static void ld_d_n(uint8_t operand) { registers.d = operand; }


////
//  E
////

// 0x1C INC E
static void inc_e(void) { registers.e = inc(registers.e); }

// 0x1D DEC E
static void dec_e(void) { registers.e = dec(registers.e); }

// 0x1E LD E,n
static void ld_e_n(uint8_t operand) { registers.e = operand; }


////
//	DE
////

// 0x11 LD DE,nn
static void ld_de_nn(uint16_t operand) { registers.de = operand; }

// 0x13 INC DE
static void inc_de(void) {	registers.de++; }

// 0x1B DEC DE
static void dec_de(void) {	registers.de--; }


////
//  H
////

// 0x24 INC H
static void inc_h(void) { registers.h = inc(registers.h); }

// 0x25 DEC H
static void dec_h(void) { registers.h = dec(registers.h); }

// 0x26 LD H,n
static void ld_h_n(uint8_t operand) { registers.h = operand; }


////
//  L
////

// 0x2C INC L
static void inc_l(void) { registers.l = inc(registers.l); }

// 0x2D DEC L
static void dec_l(void) { registers.l = dec(registers.l); }

// 0x2E LD L,n
static void ld_l_n(uint8_t operand) { registers.l = operand; }


////
//	HL
////

// 0x09 ADD HL,BC
static void add_hl_bc(void) { registers.hl = add_nn(registers.hl, registers.bc); }

// 0x21 LD HL,nn
static void ld_hl_nn(uint16_t operand) { registers.hl = operand; }

// 0x22 LD (HL+),A
//static void ldi_hl_a(void) { }

// 0x23 INC HL
static void inc_hl(void) {	registers.hl++; }

// 0x2B DEC HL
static void dec_hl(void) {	registers.hl--; }

// 0x32 LDD (HL-),A
//static void ldd_hl_a(void) { }


////
//	SP
////

// 0x31 LD SP,nn
static void ld_sp_nn(uint16_t operand) { registers.sp = operand; }

// 0x33 INC SP
static void inc_sp(void) { registers.sp++; }

// 0x3B DEC SP
static void dec_sp(void) { registers.sp--; }
