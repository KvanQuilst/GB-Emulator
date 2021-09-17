/*
 * instructions.h
 *
 * contains the prototypes for all instructions
 */

#pragma once

#include <stdint.h>

static void undefined(void);

static uint8_t inc(uint8_t val);
static uint8_t dec(uint8_t val);
static uint16_t add_nn(uint16_t val1, uint16_t val2);

static void nop(void);

static void inc_a(void);
static void dec_a(void);

static void inc_b(void);
static void dec_b(void);
static void ld_b_n(uint8_t operand);

static void inc_c(void);
static void dec_c(void);
static void ld_c_n(uint8_t operand);

static void ld_bc_nn(uint16_t operand);
static void inc_bc(void);
static void dec_bc(void);

static void inc_d(void);
static void dec_d(void);
static void ld_d_n(uint8_t operand);

static void inc_e(void);
static void dec_e(void);
static void ld_e_n(uint8_t operand);

static void ld_de_nn(uint16_t operand);
static void inc_de(void);
static void dec_de(void);

static void inc_h(void);
static void dec_h(void);
static void ld_h_n(uint8_t operand);

static void inc_l(void);
static void dec_l(void);
static void ld_l_n(uint8_t operand);

static void add_hl_bc(void);
static void ld_hl_nn(uint16_t operand);
//static void ldi_hl_a(void);
static void inc_hl(void);
static void dec_hl(void);
//static void ldd_hl_a(void);

static void ld_sp_nn(uint16_t operand);
static void inc_sp(void);
static void dec_sp(void);
