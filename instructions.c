/*
 * instructions.c
 *
 *  instruction set
 */

#include <stdint.h>
#include <stdio.h>

struct instruction {
    char *dissas;
    uint8_t operandLendth;
    void *execute;
};
extern instruction[256];

const struct instruction instructions[256] = {
    {"NOP", 0, NULL},
    {"", 0, NULL}
};

/*
 * nn - A, B, C, D, E, H. L
 * n  - 8bit immediate value
 * r  - A, B, C, D, E, H, L, (HL)
 */
void instruct(uint8_t code)
{
    switch (code) {

        ////
        //  LD   nn, n (8 cycles) - unfinished
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

        ////
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

        default:
            fprintf(stderr, "no instruction: %u\n", code);
            break;
    }
}