/*
 * cpu.c
 *
 * handles the instruction processing
 * 
 */

#include "instructions.h"
#include "memory.h"
#include "registers.h"

#include "cpu.h"
const struct instruction instr[256] =
{
    {"nop",	0, nop, 1},										// 0x00
    {"LD	BC,nn", 2, ld_bc_nn, 3},				// 0x01 
    {"LD	(BC),A", 0, undefined, 2},			// 0x02
    {"INC	BC", 0, inc_bc, 2},							// 0x03
    {"INC	B", 0, inc_b, 1},								// 0x04
    {"DEC	B", 0, dec_b, 1},								// 0x05
    {"LD	B,n", 1, ld_b_n, 2},						// 0x06
    {"RLCA", 0, undefined, 1},						// 0x07
    {"LD	(nn),SP", 2, undefined, 5},			// 0x08
    {"ADD	HL,BC", 0, add_hl_bc, 2},				// 0x09
    {"LD	A,(BC)", 0, ld_a_bc, 2},				// 0x0A
    {"DEC	BC", 0, dec_bc, 2},							// 0x0B
    {"INC	C", 0, inc_c, 1},								// 0x0C
    {"DEC	C", 0, dec_c, 1},								// 0x0D
    {"LD	C,n", 1, ld_c_n, 2},						// 0x0E
    {"RRCA", 0, undefined, 1},						// 0x0F
    {"STOP	n", 1, undefined, 1},					// 0x10
    {"LD	DE,nn", 2, ld_de_nn, 3},				// 0x11
    {"LD	(DE),A", 0, ld_a_de, 2},				// 0x12
    {"INC	DE", 0, inc_de, 2},							// 0x13
    {"INC	D", 0, inc_d, 1},								// 0x14
    {"DEC	D", 0, dec_d, 1},								// 0x15
    {"LD	D,n", 1, ld_d_n, 2},						// 0x16
    {"RLA", 0, undefined, 1},							// 0X17
    {"JR	n", 1, undefined, 3},						// 0x18
    {"ADD	HL,DE", 0, add_hl_de, 2},				// 0x19
    {"LD	A,(DE)", 0, undefined, 2},			// 0x1A
    {"DEC	DE", 0, dec_de, 2},							// 0x1B
    {"INC	E", 0, inc_e, 1},								// 0x1C
    {"DEC	E", 0, dec_e, 1},								// 0x1D
    {"LD	E,n", 1, ld_e_n, 2},						// 0x1E
    {"RRA", 0, undefined, 1},							// 0x1F
    {"STOP", 0, undefined, 2},						// 0x20
    {"LD	HL,nn", 2, ld_hl_nn, 3},				// 0x21 timing is 2 or 3
    {"LD	(HL+),A", 0, undefined, 2},			// 0X22
    {"INC	HL", 0, inc_hl, 2},							// 0x23
    {"INC	H", 0, inc_h, 1},								// 0x24
    {"DEC	H", 0, dec_h, 1},								// 0x25
    {"LD	H,n", 1, ld_h_n, 2},						// 0x26
    {"DAA", 0, undefined, 1},							// 0x27
    {"JR	Z,n", 1, undefined, 3},					// 0x28 timing is 2 or 3
    {"ADD	HL,HL", 0, add_hl_hl, 2},				// 0x29
    {"LD	A,(HL+)", 0, undefined, 2},			// 0x2A
    {"DEC	HL", 0, dec_hl, 2},							// 0x2B
    {"INC	L", 0, inc_l, 1},								// 0x2C
    {"DEC	L", 0, dec_l, 1},								// 0x2D
    {"LD	L,n", 1, ld_l_n, 2},						// 0x2E
    {"CPL", 0, cpl, 1},										// 0x2F
    {"JR	NC,n", 0, undefined, 3},				// 0x30 timing is 2 or 3
    {"LD	SP,nn", 2, ld_sp_nn, 3},				// 0x31
    {"LD	(HL-),A", 0, undefined, 2},			// 0x32
    {"INC	SP", 0, inc_sp, 2},							// 0x33
    {"INC	(HL)", 0, undefined, 3},				// 0x34
    {"DEC	(HL)", 0, undefined, 3},				// 0x35
    {"LD	(HL),n", 0, undefined, 3},			// 0x36
    {"SCF", 0, scf, 1},										// 0x37
    {"JR	C,n", 0, undefined, 3},					// 0x38 time is 2 or 3
    {"ADD	HL,SP", 0, add_hl_sp, 2},				// 0x39
    {"LD	A,(HL-)", 0, undefined, 2},			// 0x3A
    {"DEC	SP", 0, dec_sp, 2},							// 0x3B
    {"INC	A", 0, inc_a, 1},								// 0x3C
    {"DEC	A", 0, dec_a, 1},								// 0x3D
    {"LD	A,n", 0, ld_a_n, 2},						// 0x3E
    {"CCF", 0, ccf, 1},										// 0x3F
    {"LD	B,B", 0, nop, 1},								// 0x40
    {"LD	B,C", 0, ld_b_c, 1},						// 0x41
    {"LD	B,D", 0, ld_b_d, 1},						// 0x42
    {"LD	B,E", 0, ld_b_e, 1},						// 0x43
    {"LD	B,H", 0, ld_b_h, 1},						// 0x44
    {"LD	B,L", 0, ld_b_l, 1},						// 0x45
    {"LD	B,(HL)", 0, undefined, 2},			// 0x46
    {"LD	B,A", 0, ld_b_a, 1},						// 0x47
    {"LD	C,B", 0, ld_c_b, 1},						// 0x48
    {"LD	C,C", 0, nop, 1},								// 0x49
    {"LD	C,D", 1, ld_c_d, 1},						// 0x4A
    {"LD	C,E", 0, ld_c_e, 1},						// 0x4B
    {"LD	C,H", 0, ld_c_h, 1},						// 0x4C
    {"LD	C,L", 0, ld_c_l, 1},						// 0x4D
    {"LD	C,(HL)", 0, undefined, 2},			// 0x4E
    {"LD	C,A", 0, ld_c_a, 1},						// 0x4F
    {"LD	D,B", 0, ld_d_b, 1},						// 0x50
    {"LD	D,C", 0, ld_d_c, 1},						// 0x51
    {"LD	D,D", 0, nop, 1},								// 0x52
    {"LD	D,E", 0, ld_d_e, 1},						// 0x53
    {"LD	D,H", 0, ld_d_h, 1},						// 0x54
    {"LD	D,L", 0, ld_d_l, 1},						// 0x55
    {"LD	D,(HL)", 0, undefined, 2},			// 0x56
    {"LD	D,A", 0, ld_d_a, 1},						// 0x57
    {"LD	E,B", 0, ld_e_b, 1},						// 0x58
    {"LD	E,C", 0, ld_e_c, 1},						// 0x59
    {"LD	E,D", 0, ld_e_d, 1},						// 0x5A
    {"LD	E,E", 0, nop, 1},								// 0x5B
    {"LD	E,H", 0, ld_e_h, 1},						// 0x5C
    {"LD	E,L", 0, ld_e_l, 1},						// 0x5D
    {"LD	E,(HL)", 0, undefined, 2},			// 0x5E
    {"LD	E,A", 0, ld_e_a, 1},						// 0x5F
    {"LD	H,B", 0, ld_h_b, 1},						// 0x60
    {"LD	H,C", 0, ld_h_c, 1},						// 0x61
    {"LD	H,D", 0, ld_h_d, 1},						// 0x62
    {"LD	H,E", 0, ld_h_e, 1},						// 0x63
    {"LD	H,H", 0, nop, 1},								// 0x64
    {"LD	H,L", 0, ld_h_l, 1},						// 0x65
    {"LD	H,(HL)", 0, undefined, 2},			// 0x66
    {"LD	H,A", 0, ld_h_a, 1},						// 0x67
    {"LD	L,B", 0, ld_l_b, 1},						// 0x68
    {"LD	L,C", 0, ld_l_c, 1},						// 0x69
    {"LD	L,D", 0, ld_l_d, 1},						// 0x6A
    {"LD	L,E", 0, ld_l_e, 1},						// 0x6B
    {"LD	L,H", 0, ld_l_h, 1},						// 0x6C
    {"LD	L,L", 0, nop, 1},								// 0x6D
    {"LD	L,(HL)", 0, undefined, 2},			// 0x6E
    {"LD	L,A", 0, ld_l_a, 1},						// 0x6F
    {"LD	(HL),B", 0, undefined, 2},			// 0x70
    {"LD	(HL),C", 0, undefined, 2},			// 0x71
    {"LD	(HL),D", 0, undefined, 2},			// 0x72
    {"LD	(HL),E", 0, undefined, 2},			// 0x73
    {"LD	(HL),H", 0, undefined, 2},			// 0x74
    {"LD	(HL),L", 0, undefined, 2},			// 0x75
    {"HALT", 0, undefined, 1},						// 0x76
    {"LD	(HL),A", 0, undefined, 2},			// 0x77
    {"LD	A,B", 0, ld_a_b, 1},						// 0x78
    {"LD	A,C", 0, ld_a_c, 1},						// 0x79
    {"LD	A,D", 0, ld_a_d, 1},						// 0x7A
    {"LD	A,E", 0, ld_a_e, 1},						// 0x7B
    {"LD	A,H", 0, ld_a_h, 1},						// 0x7C
    {"LD	A,L", 0, ld_a_l, 1},						// 0x7D
    {"LD	A,(HL)", 0, ld_a_hl, 2},				// 0x7E
    {"LD	A,A", 0, nop, 1},								// 0x7F
    {"ADD	A,B", 0, add_b, 1},							// 0x80
    {"ADD	A,C", 0, add_c, 1},							// 0x81
    {"ADD	A,D", 0, add_d, 1},							// 0x82
    {"ADD	A,E", 0, add_e, 1},							// 0x83
    {"ADD	A,H", 0, add_h, 1},							// 0x84
    {"ADD	A,L", 0, add_l, 1},							// 0x85
    {"ADD	A,(HL)", 0, undefined, 2},			// 0x86
    {"ADD	A,A", 0, add_a, 1},							// 0x87
    {"ADC	A,B", 0, undefined, 1},					// 0x88
    {"ADC	A,C", 0, undefined, 1},					// 0x89
    {"ADC	A,D", 0, undefined, 1},					// 0x8A
    {"ADC	A,E", 0, undefined, 1},					// 0x8B
    {"ADC	A,H", 0, undefined, 1},					// 0x8C
    {"ADC	A,L", 0, undefined, 1},					// 0x8D
    {"ADC	A,(HL)", 0, undefined, 2},			// 0x8E
    {"ADC	A,A", 0, undefined, 1},					// 0x8F
    {"SUB	B", 0, sub_b, 1},								// 0x90
    {"SUB	C", 0, sub_c, 1},								// 0x91
    {"SUB	D", 0, sub_d, 1},								// 0x92
    {"SUB	E", 0, sub_e, 1},								// 0x93
    {"SUB	H", 0, sub_h, 1},								// 0x94
    {"SUB	L", 0, sub_l, 1},								// 0x95
    {"SUB	(HL)", 0, undefined, 2},				// 0x96
    {"SUB	A", 0, sub_a, 1},								// 0x97
    {"SBC	A,B", 0, undefined, 1},					// 0x98
    {"SBC	A,C", 0, undefined, 1},					// 0x99
    {"SBC	A,D", 0, undefined, 1},					// 0x9A
    {"SBC	A,E", 0, undefined, 1},					// 0x9B
    {"SBC	A,H", 0, undefined, 1},					// 0x9C
    {"SBC	A,L", 0, undefined, 1},					// 0x9D
    {"SBC	A,(HL)", 0, undefined, 2},			// 0x9E
    {"SBC	A,A", 0, undefined, 1},					// 0x9F
    {"AND	B", 0, and_b, 1},								// 0xA0
    {"AND	C", 0, and_c, 1},								// 0xA1
    {"AND	D", 0, and_d, 1},								// 0xA2
    {"AND	E", 0, and_e, 1},								// 0xA3
    {"AND	H", 0, and_h, 1},								// 0xA4
    {"AND	L", 0, and_l, 1},								// 0xA5
    {"AND	(HL)", 0, undefined, 2},				// 0xA6
    {"AND	A", 0, and_a, 1},								// 0xA7
    {"XOR	B", 0, xor_b, 1},								// 0xA8
    {"XOR	C", 0, xor_c, 1},								// 0xA9
    {"XOR	D", 0, xor_d, 1},								// 0xAA
    {"XOR	E", 0, xor_e, 1},								// 0xAB
    {"XOR	H", 0, xor_h, 1},								// 0xAC
    {"XOR	L", 0, xor_l, 1},								// 0xAD
    {"XOR	(HL)", 0, undefined, 2},				// 0xAE
    {"XOR	A", 0, xor_a, 1},								// 0xAF
    {"OR	B", 0, or_b, 1},								// 0xB0
    {"OR	C", 0, or_c, 1},								// 0xB1
    {"OR	D", 0, or_d, 1},								// 0xB2
    {"OR	E", 0, or_e, 1},								// 0xB3
    {"OR	H", 0, or_h, 1},								// 0xB4
    {"OR	L", 0, or_l, 1},								// 0xB5
    {"OR	(HL)", 0, undefined, 2},				// 0xB6
    {"OR	A", 0, or_a, 1},								// 0xB7
    {"CP	B", 0, cp_b, 1},								// 0xB8
    {"CP	C", 0, cp_c, 1},								// 0xB9
    {"CP	D", 0, cp_d, 1},								// 0xBA
    {"CP	E", 0, cp_e, 1},								// 0xBB
    {"CP	H", 0, cp_h, 1},								// 0xBC
    {"CP	L", 0, cp_l, 1},								// 0xBD
    {"CP	(HL)", 0, undefined, 2},				// 0xBE
    {"CP	A", 0, cp_a, 1},								// 0xBF
    {"RET	NZ", 0, undefined, 5},					// 0xC0 timing 2 or 5
    {"POP	BC", 0, pop_bc, 3},							// 0xC1
    {"JP	NZ,nn", 2, undefined, 4},				// 0xC2 timing 3 or 4
    {"JP	nn", 2, jp_nn, 3},							// 0xC3
    {"CALL	NZ,nn", 2, call_nz, 6},				// 0xC4 timing 3 or 6
    {"PUSH	BC", 0, push_bc, 4},					// 0xC5
    {"ADD	A,n", 1, add_n, 2},							// 0xC6
    {"RST	00H", 0, rst_00, 4},						// 0xC7
    {"RET	Z", 0, undefined, 5},						// 0xC8 timing 2 or 5
    {"RET", 0, undefined, 4},							// 0xC9
    {"JP	Z,nn", 2, undefined, 4},				// 0xCA timing 3 or 4
    {"PREFIX", 0, undefined, 1},					// 0xCB
    {"CALL	Z,nn", 2, call_z, 6},					// 0xCC timing 3 or 6
    {"CALL	nn", 2, call_nn, 6},					// 0xCD
    {"ADC	A,n", 1, undefined, 2},					// 0xCE
    {"RST	08H", 0, rst_08, 4},						// 0xCF
    {"RET	NC", 0, undefined, 5},					// 0xD0 timing 2 or 5
    {"POP	DE", 0, pop_de, 3},							// 0xD1
    {"JP	NC,nn", 2, undefined, 4},				// 0xD2 timing 3 or 4
    {"undefined", 0, undefined, 0},				// 0xD3
    {"CALL	NC,nn", 2, call_nc, 6},				// 0xD4 timing 3 or 6
    {"PUSH	DE", 0, push_de, 4},					// 0xD5
    {"SUB	n", 1, sub_n, 2},								// 0xD6
    {"RST	10H", 0, rst_10, 4},						// 0xD7
    {"RET	C", 0, undefined, 5},						// 0xD8	timing 2 or 5
    {"RETI", 0, undefined, 4},						// 0xD9
    {"JP	C,nn", 2, undefined, 4},				// 0xDA timing 3 or 4
    {"undefined", 0, undefined, 0},				// 0xDB
    {"CALL	C,nn", 2, call_c, 6},					// 0xDC timing 3 or 6
    {"undefined", 0, undefined, 0},				// 0xDD
    {"SBC	A,n", 1, undefined, 2},					// 0xDE
    {"RST	18H", 0, rst_18, 4},						// 0xDF
    {"LDH	(n),A", 1, ldh_n_a, 3},					// 0xE0
    {"POP	HL", 0, pop_hl, 3},							// 0xE1
    {"LD	(C),A", 0, undefined, 2},				// 0xE2
    {"undefined", 0, undefined, 0},				// 0xE3
    {"undefined", 0, undefined, 0},				// 0xE4
    {"PUSH	HL", 0, push_hl, 4},					// 0xE5
    {"AND	n", 1, and_n, 2},								// 0xE6
    {"RST	20H", 0, rst_20, 4},						// 0xE7
    {"ADD	SP,n", 1, add_sp, 4},						// 0xE8
    {"JP	HL", 0, undefined, 1},					// 0xE9
    {"LD	(nn),A", 2, undefined, 3},			// 0xEA
    {"undefined", 0, undefined, 0},				// 0xEB
    {"undefined", 0, undefined, 0},				// 0xEC
    {"undefined", 0, undefined, 0},				// 0xED
		{"XOR	n", 1, xor_n, 2},								// 0xEE
    {"RST	28H", 0, rst_28, 2},						// 0xEF
    {"LDH	A,(n)", 1, ldh_a_n, 2},					// 0xF0
    {"POP	AF", 0, pop_af, 3},							// 0xF1
    {"LD	A,(C)", 0, undefined, 2},				// 0xF2
    {"DI", 0, undefined, 1},							// 0xF3
    {"undefined", 0, undefined, 0},				// 0xF4
    {"PUSH	AF", 0, push_af, 4},					// 0xF5
    {"OR	n", 1, or_n, 2},								// 0xF6
    {"RST	30H", 0, rst_30, 4},						// 0xF7
    {"LD	HL,SP+n", 1, undefined, 3},			// 0xF8
    {"LD	HL,SP", 0, undefined, 2},				// 0xF9
    {"LD	A,(nn)", 2, undefined, 4},			// 0xFA
    {"EI", 0, undefined, 1},							// 0xFB
    {"undefined", 0, undefined, 0},				// 0xFC
    {"undefined", 0, undefined, 0},				// 0xFD
    {"CP	n", 1, cp_n, 2},								// 0xFE
    {"RST	38H", 0, rst_38, 4}							// 0xFF
};

uint8_t cpu_step(void)
{
	//printf("cpu_step\n");
	uint8_t instruction = read_byte(registers.pc);

	printf("0x%04x: %s\n", registers.pc, instr[instruction].disas);	

	switch (instr[instruction].ops) {

		case 0:
			registers.pc++;
			break;
		
		case 1:
			registers.pc+=2;
			break;

		case 2:
			registers.pc+=3;
			break;
	}
	return 1;
}

// for any instructions that are not defined
static void undefined(void)
{
    printf("this instruction is undefined\n");
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
static void add_sp(uint8_t val)
{
	uint32_t result = registers.sp + val;
	registers.f &= !(ALL_FLAGS);
	registers.f |= (result & 0xffff0000) * CARRY_FLAG
		+ ((registers.sp & 0x0fff)+(val & 0x0fff)>0x0fff)*HALF_FLAG;
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
	write_stack(registers.af);
	registers.sp -= 2;
}

////
//	PC
////

// 0xC3 JP,nn
static void jp_nn(uint16_t add) { registers.pc = add; }
