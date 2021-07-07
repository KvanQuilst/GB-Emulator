/*
 * instructions.c
 *
 *  instruction set
 */

#include <stdint.h>
#include <stdio.h>

/*
 * nn - A, B, C, D, E, H. L
 * n  - 8bit immediate value
 * r  - A, B, C, D, E, H, L, (HL)
 */
void instruct(uint8_t code)
{
    switch (code) {

        //// 8-bit loads

        ////TODO
        //  LD   nn, n (8 cycles)
        //  Put value n into nn
        ////

        /* LD   B, n */
        case 0x06:
            break;
        
        /* LD   C, n */
        case 0x0E:
            break;

        /* LD   D, n */
        case 0x16:
            break;

        /* LD   E, n */
        case 0x1E:
            break;

        /* LD   H, n */
        case 0x26:
            break;

        /* LD   L, n */
        case 0x2E:
            break;

        ////TODO
        // LD    r1, r2 (4 cycles) - unfinished
        //   Put value r2 into r1
        ////

        /* LD   A, A */
        case 0x7F:
            break;

        /* LD   A, B */
        case 0x78:
            break;

        /* LD   A, C */
        case 0x79:
            break;

        /* LD   A, D */
        case 0x7A:
            break;

        /* LD   A, E */
        case 0x7B:
            break;

        /* LD   A, H */
        case 0x7C:
            break;

        /* LD   A, L */
        case 0x7D:
            break;

        /* LD   A, (HL) (8 cycles) */
        case 0x7E:
            break;

        /* LD   B, B */
        case 0x40:
            break;

        /* LD   B, C */
        case 0x41:
            break;

        /* LD   B, D */
        case 0x42:
            break;

        /* LD   B, E */
        case 0x43:
            break;

        /* LD   B, H */
        case 0x44:
            break;

        /* LD   B, L */
        case 0x45:
            break;

        /* LD   B, (HL) (8 cycles) */
        case 0x46:
            break;

        /* LD   C, B */
        case 0x48:
            break;

        /* LD   C, C */
        case 0x49:
            break;

        /* LD   C, D */
        case 0x4A:
            break;

        /* LD   C, E */
        case 0x4B:
            break;

        /* LD   C, H */
        case 0x4C:
            break;

        /* LD   C, L */
        case 0x4D:
            break;

        /* LD   C, (HL) (8 cycles) */
        case 0x4E:
            break;       

        /* LD   D, B */
        case 0x50:
            break;

        /* LD   D, C */
        case 0x51:
            break;

        /* LD   D, D */
        case 0x52:
            break;

        /* LD   D, E */
        case 0x53:
            break;

        /* LD   D, H */
        case 0x54:
            break;

        /* LD   D, L */
        case 0x55:
            break;

        /* LD   D, (HL) (8 cycles) */
        case 0x56:
            break;

        /* LD   E, B */
        case 0x58:
            break;

        /* LD   E, C */
        case 0x59:
            break;

        /* LD   E, D */
        case 0x5A:
            break;

        /* LD   E, E */
        case 0x5B:
            break;

        /* LD   E, H */
        case 0x5C:
            break;

        /* LD   E, L */
        case 0x5D:
            break;

        /* LD   E, (HL) (8 cycles) */
        case 0x5E:
            break;

        /* LD   H, B */
        case 0x60:
            break;

        /* LD   H, C */
        case 0x61:
            break;

        /* LD   H, D */
        case 0x62:
            break;

        /* LD   H, E */
        case 0x63:
            break;

        /* LD   H, H */
        case 0x64:
            break;

        /* LD   H, L */
        case 0x65:
            break;
        
        /* LD   H, (HL) (8 cycles) */
        case 0x66:
            break;

        /* LD   L, B */
        case 0x68:
            break;

        /* LD   L, C */
        case 0x69:
            break;

        /* LD   L, D */
        case 0x6A:
            break;

        /* LD   L, E */
        case 0x6B:
            break;

        /* LD   L, H */
        case 0x6C:
            break;

        /* LD   L, L */
        case 0x6D:
            break;

        /* LD   L, (HL) (8 cycles) */
        case 0x6E:
            break;

        /* LD   (HL), B (8 cycles) */
        case 0x70:
            break;

        /* LD   (HL), C (8 cycles) */
        case 0x71:
            break;

        /* LD   (HL), D (8 cycles) */
        case 0x72:
            break;

        /* LD   (HL), E (8 cycles) */
        case 0x73:
            break;

        /* LD   (HL), H (8 cycles) */
        case 0x74:
            break;

        /* LD   (HL), L (8 cycles) */
        case 0x75:
            break;

        /* LD   (HL), n (12 cycles) */
        case 0x36:
            break;

        ////TODO
        //  LD   A, n (4 cycles)
        //  put value n into A
        ////

        /* LD   A, (BC) (8 cycles) */
        case 0x0A:
            break;

        /* LD   A, (DE) (8 cycles) */
        case 0x1A:
            break;

        /* LD   A, (nn) (16 cycles) */        
        case 0xFA:
            break;

        /* LD   A, # (8 cycles) */
        case 0x3E:
            break;

        ////TODO
        //  LD   n, A (4 cycles) */
        //  Put value A into n
        ////

        /* LD   B, A */
        case 0x47:
            break;

        /* LD   C, A */
        case 0x4F:
            break;

        /* LD   D, A */
        case 0x57:
            break;

        /* LD  E, A */
        case 0x5F:
            break;

        /* LD  H, A */
        case 0x67:
            break;

        /* LD  L, A */
        case 0x6F:
            break;

        /* LD   (BC), A (8 cycles) */
        case 0x02:
            break;

        /* LD   (DE), A (8 cycles) */
        case 0x12:
            break;

        /* LD   (HL), A (8 cycles) */
        case 0x77:
            break;

        /* LD   (nn), A (16 cycles) */
        case 0xEA:
            break;

        ////TODO
        //  LD   A, (C) (8 cycles)
        //  Put value at $FF00 + register C into A
        //  Same as LD   A, ($FF00+C)
        ////
        case 0xF2:
            break;

        ////TODO
        //  LD   (C), A (8 cycles)
        //  Put A into address $FF00 + register C
        ////
        case 0xE2:
            break;

        ////TODO
        //  LDD  A, (HL) (8 cycles)
        //  LD   A, (HLD)
        //  LD   A, (HL-)
        //  Put value at HL into A; decrement HL
        //  Same as LD   A, (HL) - DEC HL
        ////
        case 0x3A:
            break;

        ////TODO
        //  LDD  (HL), A (8 cycles)
        //  LD   (HL-), A 
        //  LD   (HLD), A
        //  Put A into memory address HL; decrement HL
        //  Same as LD   (HL), A - DEC HL
        ////
        case 0x32:
            break;

        ////TODO
        //  LDI  A, (HL) (8 cycles)
        //  LD   A, (HLI)
        //  LD   A, (HL+)
        //  Put value at address HL into A; increment HL
        //  Same as LD   A, (HL) - INC HL
        ////
        case 0x2A:
            break;

        ////TODO
        //  LDI  (HL), A (8 cycles)
        //  LD   (HLI), A
        //  LD   (HL+), A
        //  Put A into memory addres HL; increment HL
        //  Same as LD   (HL), A - INC HL
        ////
        case 0x22:
            break;
        
        ////TODO
        //  LDH  (n), A (12 cycles)
        //  LD   ($FF00+n), A 
        //  Put A into memory address $FF00+n
        //  n = one byte immediate value
        ////
        case 0xE0:
            break;

        ////TODO
        //  LDH  A, (n) (12 cycles)
        //  LD   A, ($FF00)
        //  Put memory address $FF00+n into A
        ////
        case 0xF0:
            break;

        ////TODO
        //  ADD  A, n (4 cycles)
        //  Add n to A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Z - Set if result is zero
        //         N - Reset
        //         H - Set if carry from bit 3
        //         C - Set if carry from bit 7
        ////
        
        /* ADD  A, A */
        case 0x87:
            break;

        /* ADD  A, B */
        case 0x80:
            break;

        /* ADD  A, C */
        case 0x81:
            break;

        /* ADD  A, D */
        case 0x82:
            break;

        /* ADD  A, E */
        case 0x83:
            break;

        /* ADD  A, H */
        case 0x84:
            break;

        /* ADD  A, L */
        case 0x85:
            break;

        /* ADD  A, (HL) (8 cycles) */
        case 0x86:
            break;

        /* ADD  A, # (8 cycles) */
        case 0xC6:
            break;

        ////TODO
        //  ADC  A, n (4 cycles)
        //  Add n + Carry Flag (H, C) to A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Check above
        ////
        
        /* ADC  A, A */
        case 0x8F:
            break;

        /* ADC  A, B */
        case 0x88:
            break;

        /* ADC  A, C */
        case 0x89:
            break;

        /* ADC  A, D */
        case 0x8A:
            break;

        /* ADC  A, E */
        case 0x8B:
            break;

        /* ADC  A, H */
        case 0x8C:
            break;

        /* ADC  A, L */
        case 0x8D:
            break;

        /* ADC  A, (HL) (8 cycles) */
        case 0x8E:
            break;

        /* ADC  A, # (8 cycles) */
        case 0xCE:
            break;

        ////TODO
        //  SUB n (4 cycles)
        //  Subtract n from A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Z - Set if result is zero
        //         N - Set
        //         H - Set if no borrow from bit 4
        //         C - Set if no borrow
        ////
        
        /* SUB  A */
        case 0x97:
            break;

        /* SUB  B */
        case 0x90:
            break;

        /* SUB  C */
        case 0x91:
            break;

        /* SUB  D */
        case 0x92:
            break;

        /* SUB  E */
        case 0x93:
            break;

        /* SUB  H */
        case 0x94:
            break;

        /* SUB  L */
        case 0x95:
            break;

        /* SUB  (HL) (8 cycles) */
        case 0x96:
            break;

        /* SUB  # (8 cycles) */
        case 0xD6:
            break;

        ////TODO
        //  SBC  A, n (4 cycles)
        //  Subtract n + Carry flag from A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: same as above

        /* SBC  A, A */
        case 0x9F:
            break;

        /* SBC  A, B */
        case 0x98:
            break;

        /* SBC  A, C */
        case 0x99:
            break;

        /* SBC  A, D */
        case 0x9A:
            break;

        /* SBC  A, E */
        case 0x9B:
            break;

        /* SBC  A, H */
        case 0x9C:
            break;
    
        /* SBC  A, L */
        case 0x9D:
            break;

        /* SBC  A, (HL) (8 cycles) */
        case 0x9E:
            break;

        /* SBC  A, # (??) */
        /* case 0x?? */

        ////TODO
        //  ADD  n (4 cycles)
        //  Logically AND n with A, result in A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Z - Set if result zero
        //         N - Reset
        //         H - Set
        //         C - Reset
        ////

        /* AND  A */
        case 0xA7:
            break;

        /* AND  B */
        case 0xA0:
            break;

        /* AND  C */
        case 0xA1:
            break;

        /* AND  D */
        case 0xA2:
            break;

        /* AND  E */
        case 0xA3:
            break;

        /* AND  H */
        case 0xA4:
            break;

        /* AND  L */
        case 0xA5:
            break;

        /* AND  (HL) (8 cycles) */
        case 0xA6:
            break;

        /* AND  # (8 cycles) */
        case 0xE6:
            break;

        ////TODO
        //  OR   n (4 cycles)
        //  Logical OR n with register A, result in A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Z - Set if result is zero
        //         N, H, C - Reset
        ////

        /* OR   A */
        case 0xB7:
            break;

        /* OR   B */
        case 0xB0:
            break;

        /* OR   C */
        case 0xB1:
            break;

        /* OR   D */
        case 0xB2:
            break;

        /* OR   E */
        case 0xB3:
            break;

        /* OR   H */
        case 0xB4:
            break;

        /* OR   L */
        case 0xB5:
            break;

        /* OR   (HL) (8 cycles) */
        case 0xB6:
            break;

        /* OR   # (8 cycles) */
        case 0xF6:
            break;

        ////TODO
        //  XOR  n (4 cycles)
        //  Logical exclusive OR n with register A; store in A
        //  n = A, B, C, D, E, H, L, (HL), #
        //  Flags: Same as above
        ////

        /* XOR  A */
        case 0xAF:
            break;

        /* XOR  B */
        case 0xA8:
            break;

        /* XOR  C */
        case 0xA9:
            break;

        /* XOR  D */
        case 0xAA:
            break;

        /* XOR  E */
        case 0xAB:
            break;

        /* XOR  H */
        case 0xAC:
            break;

        /* XOR  L */
        case 0xAD:
            break;

        /* XOR  (HL) (8 cycles) */
        case 0xAE:
            break;

        /* XOR  # (8 cycles) */
        case 0xEE:
            break;

        ////TODO
        //  CP   n (4 cycles)
        //  Compare A with n (A - n without results)
        //  n = A, B, C, D, E, H, L (HL), #
        //  Flags: Z - Set if result is zero (A = n)
        //         N - Set
        //         H - SEt if no borrow from bit 4
        //         C - Set for no borrow (A < n)
        ////

        /* CP   A */
        case 0xBF:
            break;

        /* CP   B */
        case 0xB8:
            break;

        /* CP   C */
        case 0xB9:
            break;

        /* CP   D */
        case 0xBA:
            break;

        /* CP   E */
        case 0xBB:
            break;

        /* CP   H */
        case 0xBC:
            break;

        /* CP   L */
        case 0xBD:
            break;

        /* CP  (HL) (8 cycles) */
        case 0xBE:
            break;

        /* CP   # (8 cycles) */
        case 0xFE:
            break;

        ////TODO
        //  INC  n (4 cycles)
        //  n = A, B, C, D, E, H, L (HL)
        //  Flags: Z - Set if result is zero
        //         N - Reset
        //         H - Set if carry from bit 3
        //         C - Not affected
        ////

        /* INC  A */
        case 0x3C:
            break;

        /* INC  B */
        case 0x04:
            break;

        /* INC  C */
        case 0x0C:
            break;

        /* INC  D */
        case 0x14:
            break;

        /* INC E */
        case 0x1C:
            break;

        /* INC  H */
        case 0x24:
            break;

        /* INC  L */
        case 0x2C:
            break;

        /* INC  (HL) (12 cycles) */
        case 0x34:
            break;

        ////TODO
        //  DEC  n (4 cycles)
        //  n = A, B, C, D, E, H, L, H, (HL)
        //  Flags: Z - Set if result is zero
        //         N - Set
        //         H - Set if no borrow from bit 4
        //         C - Not affected
        ////

        /* DEC  A */
        case 0x3D:
            break;

        /* DEC  B */
        case 0x05:
            break;

        /* DEC  C */
        case 0x0D:
            break;

        /* DEC  D */
        case 0x15:
            break;

        /* DEC  E */
        case 0x1D:
            break;

        /* DEC  H */
        case 0x25:
            break;

        /* DEC  L */
        case 0x2D:
            break;

        /* DEC  (HL) (12 cycles) */
        case 0x35:
            break;

        //// 16-bit loads

        ////TODO
        //  LD   n, nn (12 cycles)
        //  Put value nn into n
        //  n  = BC, DE, HL, SP
        //  nn = 16bit immediate value
        ////
        
        /* LD   BC, nn */
        case 0x01:
            break;

        /* LD   DE, nn */
        case 0x11:
            break;

        /* LD   HL, nn */
        case 0x21:
            break;

        /* LD HL, nn */
        case 0x31:
            break;

        ////TODO
        //  LD   SP, HL (8 cycles)
        //  Put HL into Stack Pointer
        ////
        case 0xF9:
            break;

        ////TODO
        //  LDHL SP, n (12 cycles)
        //  LD   HL, SP+n
        //  Put SP+n effective address into HL
        //  n = one byte signed immediate value
        //  
        //  FLAGS:
        //    Z - Reset
        //    N - Reset
        //    H - Set or reset according to operation
        //    C - Set or reset according to operation
        ////
        case 0xF8:
            break;

        ////TODO
        //  LD   (nn), SP (20 cycles)
        //  Put Stack Pointer at address n
        //  n = two byte immediate address
        ////
        case 0x08:
            break;

        ////TODO
        //  PUSH nn (16 cycles)
        //  Push register pair nn onto stack; dec SP twice
        //  nn = AF, BC, DE, HL
        ////
        
        /* PUSH AF */
        case 0xF5:
            break;

        /* PUSH BC */
        case 0xC5:
            break;

        /* PUSH DE */
        case 0xD5:
            break;
        
        /* PUSH HL */
        case 0xE5:
            break;

        ////TODO
        //  POP  nn (12 cycles)
        //  Pop two bytes off stack into register pair nn
        //  nn = AF, BC, DE, HL
        ////
        
        /* POP  AF */
        case 0xF1:
            break;

        /* POP BC */
        case 0xC1:
            break;

        /* POP DE */
        case 0xD1:
            break;

        /* POP HL */
        case 0xE1:
            break;

        ////TODO
        //  ADD  HL, n (8 cycles)
        //  Add n to HL
        //  n = BC, DE, HL, SP
        //  Flags: Z - Not affected
        //         N - Reset
        //         H - Set if carry from bit 11
        //         C - Set if carry from bit 15
        ////

        /* ADD  HL, BC */
        case 0x09:
            break;

        /* ADD  HL, DE */
        case 0x19:
            break;

        /* ADD  HL, HL */
        case 0x29:
            break;

        /* ADD  HL, SP */
        case 0x39:
            break;

        ////TODO
        //  ADD  SP, n (16 cycles)
        //  n = one byte sign immediate value (#)
        //  Flags: Z - Reset
        //         N - Reset
        //         H - Set or reset according to operation
        //         C - Set or reset according to operation
        ////
        case 0xE8:
            break;

        ////TODO
        //  INC  nn (8 cycles)
        //  Increment register nn
        //  nn = BC, DE, HL, SP
        ////

        /* INC  BC */
        case 0x03:
            break;

        /* INC  DE */
        case 0x13:
            break;

        /* INC  HL */
        case 0x23:
            break;

        /* INC  SP */
        case 0x33:
            break;

        ////TODO
        //  DEC  nn (8 cycles)
        //  Decrement register nn
        //  nn = BC, DE, HL, SP
        ////

        /* DEC  BC */
        case 0x0B:
            break;

        /* DEC  DE */
        case 0x1B:
            break;

        /* DEC  HL */
        case 0x2B:
            break;

        /* DEC  SP */
        case 0x3B:
            break;

        default:
            fprintf(stderr, "no instruction: %u\n", code);
            break;
    }
}
