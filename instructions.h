/*
 * instructions.h
 *
 * contains the prototypes for all instructions
 */

void undefined(void);

void nop(void);

void inc_a(void);
void dec_a(void);

void inc_b(void);
void dec_b(void);
void ld_b_n(uint8_t operand);

void inc_c(void);
void dec_c(void);
void ld_c_n(uint8_t operand);

void ld_bc_nn(uint16_t operand);
void inc_bc(void);
void dec_bc(void);

void inc_d(void);
void dec_d(void);
void ld_d_n(uint8_t operand);

void inc_e(void);
void dec_e(void);
void ld_e_n(uint8_t operand);

void ld_de_nn(uint16_t operand);
void inc_de(void);
void dec_de(void);

void inc_h(void);
void dec_h(void);
void ld_h_n(uint8_t operand);

void inc_l(void);
void dec_l(void);
void ld_l_n(uint8_t operand);

void ld_hl_nn(uint16_t operand);
void ldi_hl_a(void);
void ldd_hl_a(void);
void inc_hl(void);
void dec_hl(void);

void ld_sp_nn(uint16_t operand);
void inc_sp(void);
void dec_sp(void);
