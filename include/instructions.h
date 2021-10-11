/*
 * instructions.h
 *
 * contains the prototypes for all instructions
 */

#pragma once

#include <stdint.h>

// struct containing important information regarding 
// the processor instructions for GameBoy
struct instruction 
{
    char *disas;        // instruction disassembly
    uint8_t ops;        // number of operands (0-2)
    void *exec;  // function to execute instruction
    uint8_t ticks;      // machine time needed
};

static void undefined(void);

// Misc
static void nop(void);
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
//static void ldi_hl_a(void);
static void inc_hl(void);
static void add_hl_hl(void);
static void dec_hl(void);
static void add_hl_sp(void);
//static void ldd_hl_a(void);

// SP
static void ld_sp_nn(uint16_t operand);
static void inc_sp(void);
static void dec_sp(void);
static void pop_bc(void);
static void push_bc(void);
static void pop_de(void);
static void push_de(void);
static void pop_hl(void);
static void push_hl(void);
static void add_sp(uint8_t val);
static void pop_af(void);
static void push_af(void);

// PC
static void jp_nn(uint16_t add);
