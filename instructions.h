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

static uint8_t inc(uint8_t val);
static uint8_t dec(uint8_t val);
static void add(uint8_t val);
static void sub(uint8_t val);
static void add_hl(uint16_t val);

static void nop(void);

static void inc_a(void);
static void dec_a(void);
static void ld_a_n(uint8_t operand);
static void ld_a_b(void);
static void ld_a_c(void);
static void ld_a_d(void);
static void ld_a_e(void);
static void ld_a_h(void);
static void ld_a_l(void);
//static void ld_a_hla(void);
static void add_b(void);
static void add_c(void);
static void add_d(void);
static void add_e(void);
static void add_h(void);
static void add_l(void);
//static void add_hla(void);
static void add_a(void);
static void add_n(uint8_t operand);
static void sub_b(void);
static void sub_c(void);
static void sub_d(void);
static void sub_e(void);
static void sub_h(void);
static void sub_l(void);
//static void sub_hla(void);
static void sub_a(void);
static void sub_n(uint8_t operand);

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

static void ld_bc_nn(uint16_t operand);
static void inc_bc(void);
static void dec_bc(void);

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

static void ld_de_nn(uint16_t operand);
static void inc_de(void);
static void dec_de(void);

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

static void add_hl_bc(void);
static void add_hl_de(void);
static void ld_hl_nn(uint16_t operand);
//static void ldi_hl_a(void);
static void inc_hl(void);
static void add_hl_hl(void);
static void dec_hl(void);
static void add_hl_sp(void);
//static void ldd_hl_a(void);

static void ld_sp_nn(uint16_t operand);
static void inc_sp(void);
static void dec_sp(void);
