/*
 * registers.h
 * 
 * struct representation of gb registers, compatible with register
 * pairing, allowing for 16-bit registers
 * 
 * registers a-l are all 8bit registers; the stack pointer and program counter are 16bit
 * 
 *   -----------
 *  |  A  |  F  | <--- F is indirectly accessible; stores results of various math ops as well as op flags
 *  |-----------|
 *  |  B  |  C  |
 *  |-----------|
 *  |  D  |  E  |
 *  |-----------|
 *  |  H  |  L  |
 *  |-----------|
 *  |     SP    | <-- Stack Pointer (16bit)
 *  |-----------|
 *  |     PC    | <-- Program Counter (16bit)
 *   -----------
 */

#include <stdint.h>

struct registers {
    struct {
        union {
            struct {
                uint8_t a;
                uint8_t f;
            };
            uint16_t af;
        };
    };
    struct {
        union {
            struct {
                uint8_t b;
                uint8_t c;
            };
            uint16_t bc;
        };
    };
    struct {
        union {
            struct {
                uint8_t d;
                uint8_t e;
            };
            uint16_t de;
        };
    };
    struct {
        union {
            struct {
                uint8_t h;
                uint8_t l;
            };
            uint16_t hl;
        };
    };
    uint16_t sp;
    uint16_t pc;
};
extern registers;