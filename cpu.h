/*
 * cpu.h
 *
 * handles the instruction processing
 *
 */

#pragma once

#include <stdio.h>
#include <stdint.h>




void undefined(void);

void nop(void);

void inc_b(void);
void dec_b(void);
void ld_b_n(uint8_t operand);

void ld_c_n(uint8_t operand);

void ld_d_n(uint8_t operand);

void ld_e_n(uint8_t operand);

void ld_h_n(uint8_t operand);

void ld_l_n(uint8_t operand);
