/*
 * cpu.c
 *
 * handles the instruction processing
 * 
 */

#include "global.h"
#include "memory.h"
#include "registers.h"

#include "cpu.h"
#include "instructions.h"

uint8_t cpu_step(void)
{
	uint8_t instruction = read_byte(registers.pc);
	uint16_t operand;

	if (debug)
		printf("0x%04x: %s", registers.pc, instr[instruction].disas);	

	registers.pc++;
	// set ops and execute instruction
	switch (instr[instruction].ops) {

		// no operands
		case 0:
			if (debug) printRegs(0, 0);
			((void (*)(void))instr[instruction].exec)();
			break;
		
		// 1 byte operand
		case 1:
			operand = (uint16_t)read_byte(registers.pc);
			registers.pc++;
			if (debug) printRegs(operand, 1);

			((void (*)(uint8_t))instr[instruction].exec)((uint8_t)operand);
			break;

		// 2 byte operand
		case 2:
			operand = read_double(registers.pc);
			registers.pc+=2;
			if (debug) printRegs(operand, 2);

			((void (*)(uint16_t))instr[instruction].exec)(operand);
			break;
	}

	// ticks += instr[instruction].ticks;
	return 1;
}

// for any instructions that are not defined
static void undefined(void)
{
    if (debug) printf("^ this instruction is undefined\n");
		exit(1);
}

////
//  Generalized Instructions
////

// push current address onto stack
// jump to address 0x0000 + n
// requires: val to add to base
static void rst(uint8_t val)
{
	write_stack(registers.pc);
	registers.sp += 2;
	registers.pc = val;
}

// increase values and set flags
// requires: val to increase
// returns: increased value
static uint8_t inc(uint8_t val)
{

	// unset NEG_ and HALF_FLAG
	registers.f &= !(ZERO_FLAG + NEG_FLAG + HALF_FLAG); 	
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
	registers.f &= !(ZERO_FLAG + HALF_FLAG);
	registers.f |= (val & 0x0f) * HALF_FLAG;
	val--;
	registers.f |= (val == 0) * ZERO_FLAG
				+  NEG_FLAG;
	return val;
}

// add val to A and set flags
// requires: value to add
static void add(uint8_t val)
{
	uint16_t result = registers.a + val;
	
	// clear NEG_, HALF_, and CARRY_FLAG
	registers.f &= !(ALL_FLAGS);
	registers.f |= ((uint8_t) result == 0) * ZERO_FLAG
				+  (result & 0xff00) * CARRY_FLAG
				+  ((registers.a & 0x0f)+(val&0x0f)>0x0f) * HALF_FLAG;
	registers.a = (uint8_t) result;
}

// add value to HL and set flags
// requires: value to add
static void add_hl(uint16_t val)
{
	uint32_t result = registers.hl + val;

	// clear NEG_, HALF_ and CARRY_FLAG
	registers.f &= !(NEG_FLAG + HALF_FLAG + CARRY_FLAG);
	registers.f |= (result & 0xffff0000) * CARRY_FLAG
		+ ((registers.hl & 0x0fff)+(val & 0x0fff)>0x0fff)*HALF_FLAG;
	registers.hl = (uint16_t) result;
}

// sub val from A and set flags
// requires: value to sub
static void sub(uint8_t val)
{
	registers.f &= !(ZERO_FLAG + HALF_FLAG + CARRY_FLAG);
	registers.f |= (val > registers.a) * CARRY_FLAG
				+  ((val & 0x0f) > (registers.a & 0x0f)) * HALF_FLAG
				+  NEG_FLAG;
	registers.f |= ((registers.a -= val) == 0) * ZERO_FLAG;
}

// and val with A and set flags; store in A
// requires: value to and
static void and(uint8_t val)
{
	registers.f &= !(ZERO_FLAG + NEG_FLAG + CARRY_FLAG);
	registers.a &= val;
	registers.f |= (registers.a == 0) * ZERO_FLAG
				+  HALF_FLAG;
}

// xor val with A and set flags; store in A
// requires: value to xor
static void xor(uint8_t val)
{
	registers.f &= !(ALL_FLAGS);
	registers.a ^= val;
	registers.f |= (registers.a == 0) * ZERO_FLAG;
}

// or val with A and set flags; store in A
// requires: value to or
static void or(uint8_t val)
{
	registers.f &= !(ALL_FLAGS);
	registers.a |= val;
	registers.f |= (registers.a == 0) * ZERO_FLAG;
}

// compare val with A and set flags
// requires: value to compare
static void cp(uint8_t val)
{
	uint8_t result = registers.a - val;
	registers.f &= !(ZERO_FLAG + HALF_FLAG + CARRY_FLAG);
	registers.f |= (val > registers.a) * CARRY_FLAG
				+  ((val & 0x0f) > (registers.a & 0x0f)) * HALF_FLAG
				+  (result == 0) * ZERO_FLAG;
}

////
//	CPU Instructions
////

////
//  MISC
////

// 0x00 NOP
static void nop(void) {}

// 0x2F CPL
static void cpl(void)
{
	registers.f |= NEG_FLAG + HALF_FLAG;
	registers.a = !registers.a;
}

// 0x37 SCF
static void scf(void)
{
	registers.f &= !(NEG_FLAG + HALF_FLAG);
	registers.f |= CARRY_FLAG;
}

// 0x3F CCF
static void ccf(void)
{
	registers.f &= !(NEG_FLAG + HALF_FLAG);
	registers.f ^= CARRY_FLAG;
}

////
//	Calls
////

// 0xC4 CALL NZ,nn
static void call_nz(uint16_t addr)
{
	if (!(registers.f & 0x80)) registers.pc = addr;
}

// 0xCC CALL Z,nn
static void call_z(uint16_t addr)
{
	if (registers.f & 0x80) registers.pc = addr;
}

// 0xCD CALL nn
static void call_nn(uint16_t addr)
{
	write_stack(registers.pc);
	registers.sp -= 2;
	registers.pc = addr;
}

// 0xD4 CALL NC,nn
static void call_nc(uint16_t addr)
{
	if (!(registers.f & 0x10)) registers.pc = addr;
}

// 0xDC CALL C,nn
static void call_c(uint16_t addr)
{
	if (registers.f & 0x10) registers.pc = addr;
}

////
//  Restarts
////

// 0xC7 RST 00H
static void rst_00() { rst(0x00); }

// 0xCF RST 08H
static void rst_08() { rst(0x08); }

// 0xD7 RST 10H
static void rst_10() { rst(0x10); }

// 0xDF RST 18H
static void rst_18() { rst(0x18); }

// 0xE7 RST 20H
static void rst_20() { rst(0x20); }

// 0xEF RST 28H
static void rst_28() { rst(0x28); }

// 0xF7 RST 30H
static void rst_30() { rst(0x30); }

// 0xFF RST 38H
static void rst_38() { rst(0x38); }

////
//	A
////

// 0x0A LD A,(BC)
static void ld_a_bc(void) { ld_a_nn(registers.bc); }

// 0x1A LD A,(DE)
static void ld_a_de(void) { ld_a_nn(registers.de); }

// 0x3C INC A
static void inc_a(void) { registers.a = inc(registers.a); }

// 0x3D DEC A
static void dec_a(void) { registers.a = dec(registers.a); }

// 0x3E LD A,n
static void ld_a_n(uint8_t operand) { registers.a = operand; }

// 0x78 LD A,B
static void ld_a_b(void) { registers.a = registers.b; }

// 0x79 LD A,C
static void ld_a_c(void) { registers.a = registers.c; }

// 0x7A LD A,D
static void ld_a_d(void) { registers.a = registers.d; }

// 0x7B LD A,E
static void ld_a_e(void) { registers.a = registers.e; }

// 0x7C LD A,H
static void ld_a_h(void) { registers.a = registers.h; }

// 0x7D LD A,L
static void ld_a_l(void) { registers.a = registers.l; }

// 0x7E LD A,(HL)
static void ld_a_hl(void) { ld_a_nn(registers.hl); }

// 0x80 ADD A,B
static void add_b(void) { add(registers.b); }

// 0x81 ADD A,C
static void add_c(void) { add(registers.c); }

// 0x82 ADD A,D
static void add_d(void) { add(registers.d); }

// 0x83 ADD A,E
static void add_e(void) { add(registers.e); }

// 0x84 ADD A,H
static void add_h(void) { add(registers.h); }

// 0x85 ADD A,L
static void add_l(void) { add(registers.h); }

// 0x86 ADD A,(HL)

// 0x86 ADD A,A
static void add_a(void) { add(registers.a); }

// 0xC6 ADD A,n
static void add_n(uint8_t operand) { add(operand); }

// 0x90 SUB B
static void sub_b(void) { sub(registers.b); }

// 0x91 SUB C
static void sub_c(void) { sub(registers.c); }

// 0x92 SUB D
static void sub_d(void) { sub(registers.d); }

// 0x93 SUB E
static void sub_e(void) { sub(registers.e); }

// 0x94 SUB H
static void sub_h(void) { sub(registers.h); }

// 0x95 SUB L
static void sub_l(void) { sub(registers.l); }

// 0x96 SUB (HL)

// 0x97 SUB A
static void sub_a(void) { sub(registers.a); }

// 0xD6 SUB n
static void sub_n(uint8_t operand) { sub(operand); }

// 0xA0 AND B
static void and_b(void) { and(registers.b); }

// 0xA1 AND C
static void and_c(void) { and(registers.c); }

// 0xA2 AND D
static void and_d(void) { and(registers.d); }

// 0xA3 AND E
static void and_e(void) { and(registers.e); }

// 0xA4 AND H
static void and_h(void) { and(registers.h); }

// 0xA5 AND L
static void and_l(void) { and(registers.l); }

// 0xA6 AND (HL)

// 0xA7 AND A
static void and_a(void) { and(registers.a); }

// 0xE6 AND n
static void and_n(uint8_t operand) { and(operand); }

// 0xA8 XOR B
static void xor_b(void) { xor(registers.b); }

// 0xA9 XOR C
static void xor_c(void) { xor(registers.c); }

// 0xAA XOR D
static void xor_d(void) { xor(registers.d); }

// 0xAB XOR E
static void xor_e(void) { xor(registers.e); }

// 0xAC XOR H
static void xor_h(void) { xor(registers.h); }

// 0xAD XOR L
static void xor_l(void) { xor(registers.l); }

// 0xAE XOR (HL)

// 0xAF XOR A
static void xor_a(void) { xor(registers.a); }

// 0xEE XOR n
static void xor_n(uint8_t operand) { xor(operand); }

// 0xB0 OR B
static void or_b(void) { or(registers.b); }

// 0xB1 OR C
static void or_c(void) { or(registers.c); }

// 0xB2 OR D
static void or_d(void) { or(registers.d); }

// 0xB3 OR E
static void or_e(void) { or(registers.e); }

// 0xB4 OR H
static void or_h(void) { or(registers.h); }

// 0xB5 OR L
static void or_l(void) { or(registers.l); }

// 0xB6 OR (HL)

// 0xB7 OR A
static void or_a(void) { or(registers.a); }

// 0xF6 OR n
static void or_n(uint8_t operand) { or(operand); }

// 0xB8 CP B
static void cp_b(void) { cp(registers.b); }

// 0xB9 CP C
static void cp_c(void) { cp(registers.c); }

// 0xBA CP D
static void cp_d(void) { cp(registers.d); }

// 0xBB CP E
static void cp_e(void) { cp(registers.e); }

// 0xBC CP H
static void cp_h(void) { cp(registers.h); }

// 0xBD CP L
static void cp_l(void) { cp(registers.l); }

// 0xBE CP (HL)

// 0xBF CP A
static void cp_a(void) { cp(registers.a); }

// 0xE0 LDH (n),A
static void ldh_n_a(uint8_t operand)
{
	write_byte(0xFF00 + operand, registers.a);
}

// 0xF0 LDH A,(n)
static void ldh_a_n(uint8_t operand)
{
	registers.a = read_byte(0xFF00 + operand);
}

// 0xFA LD A,(nn)
static void ld_a_nn(uint16_t operand)
{
	registers.a = read_byte(operand);
}

// 0xFE CP n
static void cp_n(uint8_t operand) { cp(operand); }


////
//  B
///

// 0x04 INC B
static void inc_b(void) { registers.b = inc(registers.b); }

// 0x05 DEC B
static void dec_b(void) { registers.b = dec(registers.b); }

// 0x06 LD B,n
static void ld_b_n(uint8_t operand) { registers.b = operand; }

// 0x41 LD B,C
static void ld_b_c(void) { registers.b = registers.c; }

// 0x42 LD B,D
static void ld_b_d(void) { registers.b = registers.d; }

// 0x43 LD B,E
static void ld_b_e(void) { registers.b = registers.e; }

// 0x44 LD B,H
static void ld_b_h(void) { registers.b = registers.h; }

// 0x45 LD B,L
static void ld_b_l(void) { registers.b = registers.l; }

// 0x46 LD B,(HL)

// 0x47 LD B,A
static void ld_b_a(void) { registers.b = registers.a; }


////
//  C
////

// 0x0C INC C
static void inc_c(void) { registers.c = inc(registers.c); }

// 0x0D DEC C
static void dec_c(void) { registers.c = dec(registers.c); }

// 0x0E LD C,n
static void ld_c_n(uint8_t operand) { registers.c = operand; }

// 0x48 LD C,B
static void ld_c_b(void) { registers.c = registers.b; }

// 0x4A LD C,D
static void ld_c_d(void) { registers.c = registers.d; }

// 0x4B LD C,E
static void ld_c_e(void) { registers.c = registers.e; }

// 0x4C LD C,H
static void ld_c_h(void) { registers.c = registers.h; }

// 0x4D LD C,L
static void ld_c_l(void) { registers.c = registers.l; }

// 0x4E LD C,(HL)

//0x4F LD, C,A
static void ld_c_a(void) { registers.c = registers.a; }


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

// 0x50 LD D,B
static void ld_d_b(void) { registers.d = registers.b; }

// 0x51 LD D,C
static void ld_d_c(void) { registers.d = registers.c; }

// 0x53 LD D,E
static void ld_d_e(void) { registers.d = registers.e; }

// 0x54 LD D,H
static void ld_d_h(void) { registers.d = registers.h; }

// 0x55 LD D,L
static void ld_d_l(void) { registers.d = registers.l; }

// 0x56 LD D,(HL)

// 0x57 LD D,A
static void ld_d_a(void) { registers.d = registers.a; }


////
//  E
////

// 0x1C INC E
static void inc_e(void) { registers.e = inc(registers.e); }

// 0x1D DEC E
static void dec_e(void) { registers.e = dec(registers.e); }

// 0x1E LD E,n
static void ld_e_n(uint8_t operand) { registers.e = operand; }

// 0x58 LD E,B
static void ld_e_b(void) { registers.e = registers.b; }

// 0x59 LD E,C
static void ld_e_c(void) { registers.e = registers.c; }

// 0x5A LD E,D
static void ld_e_d(void) { registers.e = registers.d; }

// 0x5C LD E,H
static void ld_e_h(void) { registers.e = registers.h; }

// 0x5D LD E,L
static void ld_e_l(void) { registers.e = registers.l; }

// 0x5E LD E,(HL)

// 0x5F LD E,A
static void ld_e_a(void) { registers.e = registers.a; }


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

// 0x60 LD H,B
static void ld_h_b(void) { registers.h = registers.b; }

// 0x61 LD H,C
static void ld_h_c(void) { registers.h = registers.c; }

// 0x62 LD H,D
static void ld_h_d(void) { registers.h = registers.d; }

// 0x63 LD H,E
static void ld_h_e(void) { registers.h = registers.e; }

// 0x65 LD H,L
static void ld_h_l(void) { registers.h = registers.l; }

// 0x66 LD H,(HL)

// 0x67 LD H,A
static void ld_h_a(void) { registers.h = registers.a; }


////
//  L
////

// 0x2C INC L
static void inc_l(void) { registers.l = inc(registers.l); }

// 0x2D DEC L
static void dec_l(void) { registers.l = dec(registers.l); }

// 0x2E LD L,n
static void ld_l_n(uint8_t operand) { registers.l = operand; }

// 0x68 LD L,B
static void ld_l_b(void) { registers.l = registers.b; }

// 0x69 LD L,C
static void ld_l_c(void) { registers.l = registers.c; }

// 0x6A LD L,D
static void ld_l_d(void) { registers.l = registers.d; }

// 0x6B LD L,E
static void ld_l_e(void) { registers.l = registers.e; }

// 0x6C LD L,H
static void ld_l_h(void) { registers.l = registers.h; }

// 0x6E LD L,(HL)

// 0x6F LD L,A
static void ld_l_a(void) { registers.l = registers.a; }


////
//	HL
////

// 0x09 ADD HL,BC
static void add_hl_bc(void) { add_hl(registers.bc); }

// 0x19 ADD HL,DE
static void add_hl_de(void) { add_hl(registers.de); }

// 0x21 LD HL,nn
static void ld_hl_nn(uint16_t operand) { registers.hl = operand; }

// 0x22 LD (HL+),A
static void ldi_hl_a(void) { write_byte(registers.hl++, registers.a); }

// 0x22 LD (HL+),A
//static void ldi_hl_a(void) { }

// 0x23 INC HL
static void inc_hl(void) {registers.hl++; }

// 0x29 ADD HL,HL
static void add_hl_hl(void) { add_hl(registers.hl); }

// 0x2B DEC HL
static void dec_hl(void) {	registers.hl--; }

// 0x32 LDD (HL-),A
//static void ldd_hl_a(void) { }

// 0x39 ADD HL,SP
static void add_hl_sp(void) { add_hl(registers.sp); }


////
//	SP
////

// 0x31 LD SP,nn
static void ld_sp_nn(uint16_t operand) { registers.sp = operand; }

// 0x33 INC SP
static void inc_sp(void) { registers.sp++; }

// 0x3B DEC SP
static void dec_sp(void) { registers.sp--; }

// 0xC1 POP BC
static void pop_bc(void) 
{
	registers.bc = read_stack();
	registers.sp += 2;
}

// 0xC5 PUSH BC
static void push_bc(void) 
{
	write_stack(registers.bc);
	registers.sp -= 2;
}

// 0xD1 POP DE
static void pop_de(void) 
{
	registers.de = read_stack();
	registers.sp += 2;
}

// 0xD5 PUSH DE
static void push_de(void) 
{
	write_stack(registers.de);
	registers.sp -= 2;
}

// 0xE1 POP HL
static void pop_hl(void) 
{
	registers.hl = read_stack();
	registers.sp += 2;
}

// 0xE5 PUSH HL
static void push_hl(void) 
{
	write_stack(registers.hl);
	registers.sp -= 2;
}

// 0xE8 ADD SP,n
static void add_sp(uint8_t operand)
{
	uint32_t result = registers.sp + operand;
	registers.f &= !(ALL_FLAGS);
	registers.f |= (result & 0xffff0000) * CARRY_FLAG
		+ ((registers.sp & 0x0fff)+(operand & 0x0fff)>0x0fff)*HALF_FLAG;
	registers.sp = (uint16_t) result;
}

// 0xF1 POP AF
static void pop_af(void) 
{
	registers.af = read_stack();
	registers.sp += 2;
}

// 0xF5 PUSH AF
static void push_af(void) 
{
	registers.sp -= 2;
	write_stack(registers.af);
}

////
//	PC
////

// 0x18 JR n (signed)
static void jr(uint8_t operand)
{
	registers.pc += ((operand>>7) * operand & 0x7F)
							 + (!(operand>>7) * operand & 0x7F);
}

// 0x28 JR Z,n (signed)
static void jr_z(uint8_t operand) { if (registers.f >> 7) jr(operand); }

// 0xC3 JP,nn
static void jp_nn(uint16_t operand) { registers.pc = operand; }
