/*
 * registers.c
 *
 * initialize the registers struct
 *
 */

#include "registers.h"

struct registers registers;

void initRegs(void)
{
	registers.af = 0x0000;
	registers.bc = 0x0000;
	registers.de = 0x0000;
	registers.hl = 0x0000;
	registers.sp = 0xFFFE;
	registers.pc = 0x0100;
}

void printRegs(void)
{
	char flags[4] = "----";
	if (registers.f & 0x80) flags[0] = 'Z';
	if (registers.f & 0x40) flags[1] = 'N';
	if (registers.f & 0x20) flags[2] = 'H';
	if (registers.f & 0x10) flags[3] = 'C';

	/*						rF	rA  rB	rC	rD	rE	rH	rL	rSP	 rPC*/
	printf("\t| %s\t0x%02x\t0x%02x\t0x%02x\t0x%02x\t0x%02x\t",
			flags,
			registers.a,
			registers.b,
			registers.c,
			registers.d,
			registers.e);
	printf("0x%02x\t0x%02x\t0x%04x\t0x%04x\n",
			registers.h,
			registers.l,
			registers.sp,
			registers.pc);
}
