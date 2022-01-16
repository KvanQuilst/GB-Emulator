/*
 * instructions.h
 *
 * contains the prototypes for all instructions
 */

#pragma once

// struct containing important information regarding // the processor instructions for GameBoy
struct instruction 
{
    char *disas;        // instruction disassembly
    uint8_t ops;        // number of operands (0-2)
    void *exec;         // function to execute instruction
    uint8_t ticks;      // machine time needed
};

static void undefined(void);

// Misc
static void nop(void);
static void stop(void);
static void cpl(void);
static void scf(void);
static void ccf(void);

// Calls
static void call_nn(uint16_t addr);
static void call_nz(uint16_t addr);
static void call_z(uint16_t addr);
static void call_nc(uint16_t addr);
static void call_c(uint16_t addr);

// Restarts
static void rst_00(void);
static void rst_08(void);
static void rst_10(void);
static void rst_18(void);
static void rst_20(void);
static void rst_28(void);
static void rst_30(void);
static void rst_38(void);

// A
static void ld_a_bc(void);
static void ld_a_de(void);
static void inc_a(void);
static void dec_a(void);
static void ld_a_n(uint8_t operand);
static void ld_a_b(void);
static void ld_a_c(void);
static void ld_a_d(void);
static void ld_a_e(void);
static void ld_a_h(void);
static void ld_a_l(void);
static void ld_a_hl(void);
static void add_b(void);
static void add_c(void);
static void add_d(void);
static void add_e(void);
static void add_h(void);
static void add_l(void);
//static void add_hl(void);
static void add_a(void);
static void add_n(uint8_t operand);
static void sub_b(void);
static void sub_c(void);
static void sub_d(void);
static void sub_e(void);
static void sub_h(void);
static void sub_l(void);
//static void sub_hl(void);
static void sub_a(void);
static void sub_n(uint8_t operand);
static void and_b(void);
static void and_c(void);
static void and_d(void);
static void and_e(void);
static void and_h(void);
static void and_l(void);
//static void and_hl(void);
static void and_a(void);
static void and_n(uint8_t operand);
static void xor_b(void);
static void xor_c(void);
static void xor_d(void);
static void xor_e(void);
static void xor_h(void);
static void xor_l(void);
//static void xor_hl(void);
static void xor_a(void);
static void xor_n(uint8_t operand);
static void or_b(void);
static void or_c(void);
static void or_d(void);
static void or_e(void);
static void or_h(void);
static void or_l(void);
//static void or_hl(void);
static void or_a(void);
static void or_n(uint8_t operand);
static void cp_b(void);
static void cp_c(void);
static void cp_d(void);
static void cp_e(void);
static void cp_h(void);
static void cp_l(void);
//static void cp_hla(void);
static void cp_a(void);
static void ldh_n_a(uint8_t operand);
static void ld_nn_a(uint16_t operand);
static void ldh_a_n(uint8_t operand);
static void ld_a_nn(uint16_t operand);
static void cp_n(uint8_t operand);

// B
static void inc_b(void);
static void dec_b(void);
static void ld_b_n(uint8_t operand);
static void ld_b_c(void);
static void ld_b_d(void);
static void ld_b_e(void);
static void ld_b_h(void);
static void ld_b_l(void);
//static void ld_b_hla(void);
static void ld_b_a(void);

// C
static void inc_c(void);
static void dec_c(void);
static void ld_c_n(uint8_t operand);
static void ld_c_b(void);
static void ld_c_d(void);
static void ld_c_e(void);
static void ld_c_h(void);
static void ld_c_l(void);
//static void ld_c_hla(void);
static void ld_c_a(void);

// BC
static void ld_bc_nn(uint16_t operand);
static void ld_bc_a(void);
static void inc_bc(void);
static void dec_bc(void);

// D
static void inc_d(void);
static void dec_d(void);
static void ld_d_n(uint8_t operand);
static void ld_d_b(void);
static void ld_d_c(void);
static void ld_d_e(void);
static void ld_d_h(void);
static void ld_d_l(void);
//static void ld_d_hla(void);
static void ld_d_a(void);

// E
static void inc_e(void);
static void dec_e(void);
static void ld_e_n(uint8_t operand);
static void ld_e_b(void);
static void ld_e_c(void);
static void ld_e_d(void);
static void ld_e_h(void);
static void ld_e_l(void);
//static void ld_e_hla(void);
static void ld_e_a(void);

// DE
static void ld_de_nn(uint16_t operand);
static void ld_de_a(void);
static void inc_de(void);
static void dec_de(void);

// H
static void inc_h(void);
static void dec_h(void);
static void ld_h_n(uint8_t operand);
static void ld_h_b(void);
static void ld_h_c(void);
static void ld_h_d(void);
static void ld_h_e(void);
static void ld_h_l(void);
//static void ld_h_hla(void);
static void ld_h_a(void);

// L
static void inc_l(void);
static void dec_l(void);
static void ld_l_n(uint8_t operand);
static void ld_l_b(void);
static void ld_l_c(void);
static void ld_l_d(void);
static void ld_l_e(void);
static void ld_l_h(void);
//static void ld_l_hla(void);
static void ld_l_a(void);

// HL
static void add_hl_bc(void);
static void add_hl_de(void);
static void ld_hl_nn(uint16_t operand);
static void ldi_hl_a(void);
static void inc_hl(void);
static void add_hl_hl(void);
static void dec_hl(void);
static void ldd_hl_a(void);
static void add_hl_sp(void);
static void ld_hl_a(void);

// SP
static void ld_sp_nn(uint16_t operand);
static void inc_sp(void);
static void dec_sp(void);
static void pop_bc(void);
static void ret_nz(void);
static void push_bc(void);
static void ret_z(void);
static void ret(void);
static void ret_nc(void);
static void pop_de(void);
static void push_de(void);
static void ret_c(void);
static void pop_hl(void);
static void push_hl(void);
static void add_sp(uint8_t operand);
static void pop_af(void);
static void push_af(void);

// PC
static void jr(uint8_t operand);
static void jr_nz(uint8_t operand);
static void jr_z(uint8_t operand);
static void jp_nn(uint16_t operand);

////
//	Instructions array
////

const struct instruction instr[256] =
{
    {"nop\t",	0, nop, 1},									// 0x00 tab for print alignment
    {"LD	BC,nn", 2, ld_bc_nn, 3},				// 0x01 
    {"LD	(BC),A", 0, ld_bc_a, 2},				// 0x02
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
    {"STOP\t", 1, stop, 1},					      // 0x10
    {"LD	DE,nn", 2, ld_de_nn, 3},				// 0x11
    {"LD	(DE),A", 0, ld_de_a, 2},				// 0x12
    {"INC	DE", 0, inc_de, 2},							// 0x13
    {"INC	D", 0, inc_d, 1},								// 0x14
    {"DEC	D", 0, dec_d, 1},								// 0x15
    {"LD	D,n", 1, ld_d_n, 2},						// 0x16
    {"RLA", 0, undefined, 1},							// 0X17
    {"JR	n", 1, jr, 3},									// 0x18
    {"ADD	HL,DE", 0, add_hl_de, 2},				// 0x19
    {"LD	A,(DE)", 0, ld_a_de, 2},				// 0x1A
    {"DEC	DE", 0, dec_de, 2},							// 0x1B
    {"INC	E", 0, inc_e, 1},								// 0x1C
    {"DEC	E", 0, dec_e, 1},								// 0x1D
    {"LD	E,n", 1, ld_e_n, 2},						// 0x1E
    {"RRA", 0, undefined, 1},							// 0x1F
    {"JR NZ,n", 0, jr_nz, 12},		        // 0x20 timing 8 or 12
    {"LD	HL,nn", 2, ld_hl_nn, 3},				// 0x21 timing is 2 or 3
    {"LD	(HL+),A", 0, ldi_hl_a, 2},			// 0X22
    {"INC	HL", 0, inc_hl, 2},							// 0x23
    {"INC	H", 0, inc_h, 1},								// 0x24
    {"DEC	H", 0, dec_h, 1},								// 0x25
    {"LD	H,n", 1, ld_h_n, 2},						// 0x26
    {"DAA", 0, undefined, 1},							// 0x27
    {"JR	Z,n", 1, jr_z, 3},							// 0x28 timing is 2 or 3
    {"ADD	HL,HL", 0, add_hl_hl, 2},				// 0x29
    {"LD	A,(HL+)", 0, undefined, 2},			// 0x2A
    {"DEC	HL", 0, dec_hl, 2},							// 0x2B
    {"INC	L", 0, inc_l, 1},								// 0x2C
    {"DEC	L", 0, dec_l, 1},								// 0x2D
    {"LD	L,n", 1, ld_l_n, 2},						// 0x2E
    {"CPL", 0, cpl, 1},										// 0x2F
    {"JR	NC,n", 0, undefined, 3},				// 0x30 timing is 2 or 3
    {"LD	SP,nn", 2, ld_sp_nn, 3},				// 0x31
    {"LD	(HL-),A", 0, ldd_hl_a, 2},			// 0x32
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
    {"LD	(HL),A", 0, ld_hl_a, 2},				// 0x77
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
    {"RET	NZ", 0, ret_nz, 5},							// 0xC0 timing 2 or 5
    {"POP	BC", 0, pop_bc, 3},							// 0xC1
    {"JP	NZ,nn", 2, undefined, 4},				// 0xC2 timing 3 or 4
    {"JP	nn", 2, jp_nn, 3},							// 0xC3
    {"CALL	NZ,nn", 2, call_nz, 6},				// 0xC4 timing 3 or 6
    {"PUSH	BC", 0, push_bc, 4},					// 0xC5
    {"ADD	A,n", 1, add_n, 2},							// 0xC6
    {"RST	00H", 0, rst_00, 4},						// 0xC7
    {"RET	Z", 0, ret_z, 5},								// 0xC8 timing 2 or 5
    {"RET", 0, ret, 4},										// 0xC9
    {"JP	Z,nn", 2, undefined, 4},				// 0xCA timing 3 or 4
    {"PREFIX", 0, undefined, 1},					// 0xCB
    {"CALL	Z,nn", 2, call_z, 6},					// 0xCC timing 3 or 6
    {"CALL	nn", 2, call_nn, 6},					// 0xCD
    {"ADC	A,n", 1, undefined, 2},					// 0xCE
    {"RST	08H", 0, rst_08, 4},						// 0xCF
    {"RET	NC", 0, ret_nc, 5},							// 0xD0 timing 2 or 5
    {"POP	DE", 0, pop_de, 3},							// 0xD1
    {"JP	NC,nn", 2, undefined, 4},				// 0xD2 timing 3 or 4
    {"undefined", 0, undefined, 0},				// 0xD3
    {"CALL	NC,nn", 2, call_nc, 6},				// 0xD4 timing 3 or 6
    {"PUSH	DE", 0, push_de, 4},					// 0xD5
    {"SUB	n", 1, sub_n, 2},								// 0xD6
    {"RST	10H", 0, rst_10, 4},						// 0xD7
    {"RET	C", 0, ret_c, 5},								// 0xD8	timing 2 or 5
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
    {"LD	(nn),A", 2, ld_nn_a, 3},				// 0xEA
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
