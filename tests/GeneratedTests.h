#ifndef GB_ASSEMBLER_GENERATEDTESTS_H
#define GB_ASSEMBLER_GENERATEDTESTS_H

#include "Tests.h"

std::vector<OpTest> vectorTestGenerated = {
    {
        "NOP ",
        {0x00}
    },
    {
        "LD BC, $ABCD",
        {0x01, 0xCD, 0xAB}
    },
    {
        "LD [BC], A",
        {0x02}
    },
    {
        "INC BC",
        {0x03}
    },
    {
        "INC B",
        {0x04}
    },
    {
        "DEC B",
        {0x05}
    },
    {
        "LD B, 27",
        {0x06, 0x1B}
    },
    {
        "RLCA ",
        {0x07}
    },
    {
        "LD [$ABCD], SP",
        {0x08, 0xCD, 0xAB}
    },
    {
        "ADD HL, BC",
        {0x09}
    },
    {
        "LD A, [BC]",
        {0x0A}
    },
    {
        "DEC BC",
        {0x0B}
    },
    {
        "INC C",
        {0x0C}
    },
    {
        "DEC C",
        {0x0D}
    },
    {
        "LD C, 27",
        {0x0E, 0x1B}
    },
    {
        "RRCA ",
        {0x0F}
    },
    {
        "STOP ",
        {0x10, 0x00}
    },
    {
        "LD DE, $ABCD",
        {0x11, 0xCD, 0xAB}
    },
    {
        "LD [DE], A",
        {0x12}
    },
    {
        "INC DE",
        {0x13}
    },
    {
        "INC D",
        {0x14}
    },
    {
        "DEC D",
        {0x15}
    },
    {
        "LD D, 27",
        {0x16, 0x1B}
    },
    {
        "RLA ",
        {0x17}
    },
    {
        "JR -27",
        {0x18, 0xF9}
    },
    {
        "ADD HL, DE",
        {0x19}
    },
    {
        "LD A, [DE]",
        {0x1A}
    },
    {
        "DEC DE",
        {0x1B}
    },
    {
        "INC E",
        {0x1C}
    },
    {
        "DEC E",
        {0x1D}
    },
    {
        "LD E, 27",
        {0x1E, 0x1B}
    },
    {
        "RRA ",
        {0x1F}
    },
    {
        "JR NZ, -27",
        {0x20, 0xF9}
    },
    {
        "LD HL, $ABCD",
        {0x21, 0xCD, 0xAB}
    },
    {
        "LD [HL+], A",
        {0x22}
    },
    {
        "INC HL",
        {0x23}
    },
    {
        "INC H",
        {0x24}
    },
    {
        "DEC H",
        {0x25}
    },
    {
        "LD H, 27",
        {0x26, 0x1B}
    },
    {
        "DAA ",
        {0x27}
    },
    {
        "JR Z, -27",
        {0x28, 0xF9}
    },
    {
        "ADD HL, HL",
        {0x29}
    },
    {
        "LD A, [HL+]",
        {0x2A}
    },
    {
        "DEC HL",
        {0x2B}
    },
    {
        "INC L",
        {0x2C}
    },
    {
        "DEC L",
        {0x2D}
    },
    {
        "LD L, 27",
        {0x2E, 0x1B}
    },
    {
        "CPL ",
        {0x2F}
    },
    {
        "JR NC, -27",
        {0x30, 0xF9}
    },
    {
        "LD SP, $ABCD",
        {0x31, 0xCD, 0xAB}
    },
    {
        "LD [HL-], A",
        {0x32}
    },
    {
        "INC SP",
        {0x33}
    },
    {
        "INC [HL]",
        {0x34}
    },
    {
        "DEC [HL]",
        {0x35}
    },
    {
        "LD [HL], 27",
        {0x36, 0x1B}
    },
    {
        "SCF ",
        {0x37}
    },
    {
        "JR C, -27",
        {0x38, 0xF9}
    },
    {
        "ADD HL, SP",
        {0x39}
    },
    {
        "LD A, [HL-]",
        {0x3A}
    },
    {
        "DEC SP",
        {0x3B}
    },
    {
        "INC A",
        {0x3C}
    },
    {
        "DEC A",
        {0x3D}
    },
    {
        "LD A, 27",
        {0x3E, 0x1B}
    },
    {
        "CCF ",
        {0x3F}
    },
    {
        "LD B, B",
        {0x40}
    },
    {
        "LD B, C",
        {0x41}
    },
    {
        "LD B, D",
        {0x42}
    },
    {
        "LD B, E",
        {0x43}
    },
    {
        "LD B, H",
        {0x44}
    },
    {
        "LD B, L",
        {0x45}
    },
    {
        "LD B, [HL]",
        {0x46}
    },
    {
        "LD B, A",
        {0x47}
    },
    {
        "LD C, B",
        {0x48}
    },
    {
        "LD C, C",
        {0x49}
    },
    {
        "LD C, D",
        {0x4A}
    },
    {
        "LD C, E",
        {0x4B}
    },
    {
        "LD C, H",
        {0x4C}
    },
    {
        "LD C, L",
        {0x4D}
    },
    {
        "LD C, [HL]",
        {0x4E}
    },
    {
        "LD C, A",
        {0x4F}
    },
    {
        "LD D, B",
        {0x50}
    },
    {
        "LD D, C",
        {0x51}
    },
    {
        "LD D, D",
        {0x52}
    },
    {
        "LD D, E",
        {0x53}
    },
    {
        "LD D, H",
        {0x54}
    },
    {
        "LD D, L",
        {0x55}
    },
    {
        "LD D, [HL]",
        {0x56}
    },
    {
        "LD D, A",
        {0x57}
    },
    {
        "LD E, B",
        {0x58}
    },
    {
        "LD E, C",
        {0x59}
    },
    {
        "LD E, D",
        {0x5A}
    },
    {
        "LD E, E",
        {0x5B}
    },
    {
        "LD E, H",
        {0x5C}
    },
    {
        "LD E, L",
        {0x5D}
    },
    {
        "LD E, [HL]",
        {0x5E}
    },
    {
        "LD E, A",
        {0x5F}
    },
    {
        "LD H, B",
        {0x60}
    },
    {
        "LD H, C",
        {0x61}
    },
    {
        "LD H, D",
        {0x62}
    },
    {
        "LD H, E",
        {0x63}
    },
    {
        "LD H, H",
        {0x64}
    },
    {
        "LD H, L",
        {0x65}
    },
    {
        "LD H, [HL]",
        {0x66}
    },
    {
        "LD H, A",
        {0x67}
    },
    {
        "LD L, B",
        {0x68}
    },
    {
        "LD L, C",
        {0x69}
    },
    {
        "LD L, D",
        {0x6A}
    },
    {
        "LD L, E",
        {0x6B}
    },
    {
        "LD L, H",
        {0x6C}
    },
    {
        "LD L, L",
        {0x6D}
    },
    {
        "LD L, [HL]",
        {0x6E}
    },
    {
        "LD L, A",
        {0x6F}
    },
    {
        "LD [HL], B",
        {0x70}
    },
    {
        "LD [HL], C",
        {0x71}
    },
    {
        "LD [HL], D",
        {0x72}
    },
    {
        "LD [HL], E",
        {0x73}
    },
    {
        "LD [HL], H",
        {0x74}
    },
    {
        "LD [HL], L",
        {0x75}
    },
    {
        "HALT ",
        {0x76}
    },
    {
        "LD [HL], A",
        {0x77}
    },
    {
        "LD A, B",
        {0x78}
    },
    {
        "LD A, C",
        {0x79}
    },
    {
        "LD A, D",
        {0x7A}
    },
    {
        "LD A, E",
        {0x7B}
    },
    {
        "LD A, H",
        {0x7C}
    },
    {
        "LD A, L",
        {0x7D}
    },
    {
        "LD A, [HL]",
        {0x7E}
    },
    {
        "LD A, A",
        {0x7F}
    },
    {
        "ADD A, B",
        {0x80}
    },
    {
        "ADD A, C",
        {0x81}
    },
    {
        "ADD A, D",
        {0x82}
    },
    {
        "ADD A, E",
        {0x83}
    },
    {
        "ADD A, H",
        {0x84}
    },
    {
        "ADD A, L",
        {0x85}
    },
    {
        "ADD A, [HL]",
        {0x86}
    },
    {
        "ADD A, A",
        {0x87}
    },
    {
        "ADC A, B",
        {0x88}
    },
    {
        "ADC A, C",
        {0x89}
    },
    {
        "ADC A, D",
        {0x8A}
    },
    {
        "ADC A, E",
        {0x8B}
    },
    {
        "ADC A, H",
        {0x8C}
    },
    {
        "ADC A, L",
        {0x8D}
    },
    {
        "ADC A, [HL]",
        {0x8E}
    },
    {
        "ADC A, A",
        {0x8F}
    },
    {
        "SUB A, B",
        {0x90}
    },
    {
        "SUB A, C",
        {0x91}
    },
    {
        "SUB A, D",
        {0x92}
    },
    {
        "SUB A, E",
        {0x93}
    },
    {
        "SUB A, H",
        {0x94}
    },
    {
        "SUB A, L",
        {0x95}
    },
    {
        "SUB A, [HL]",
        {0x96}
    },
    {
        "SUB A, A",
        {0x97}
    },
    {
        "SBC A, B",
        {0x98}
    },
    {
        "SBC A, C",
        {0x99}
    },
    {
        "SBC A, D",
        {0x9A}
    },
    {
        "SBC A, E",
        {0x9B}
    },
    {
        "SBC A, H",
        {0x9C}
    },
    {
        "SBC A, L",
        {0x9D}
    },
    {
        "SBC A, [HL]",
        {0x9E}
    },
    {
        "SBC A, A",
        {0x9F}
    },
    {
        "AND A, B",
        {0xA0}
    },
    {
        "AND A, C",
        {0xA1}
    },
    {
        "AND A, D",
        {0xA2}
    },
    {
        "AND A, E",
        {0xA3}
    },
    {
        "AND A, H",
        {0xA4}
    },
    {
        "AND A, L",
        {0xA5}
    },
    {
        "AND A, [HL]",
        {0xA6}
    },
    {
        "AND A, A",
        {0xA7}
    },
    {
        "XOR A, B",
        {0xA8}
    },
    {
        "XOR A, C",
        {0xA9}
    },
    {
        "XOR A, D",
        {0xAA}
    },
    {
        "XOR A, E",
        {0xAB}
    },
    {
        "XOR A, H",
        {0xAC}
    },
    {
        "XOR A, L",
        {0xAD}
    },
    {
        "XOR A, [HL]",
        {0xAE}
    },
    {
        "XOR A, A",
        {0xAF}
    },
    {
        "OR A, B",
        {0xB0}
    },
    {
        "OR A, C",
        {0xB1}
    },
    {
        "OR A, D",
        {0xB2}
    },
    {
        "OR A, E",
        {0xB3}
    },
    {
        "OR A, H",
        {0xB4}
    },
    {
        "OR A, L",
        {0xB5}
    },
    {
        "OR A, [HL]",
        {0xB6}
    },
    {
        "OR A, A",
        {0xB7}
    },
    {
        "CP A, B",
        {0xB8}
    },
    {
        "CP A, C",
        {0xB9}
    },
    {
        "CP A, D",
        {0xBA}
    },
    {
        "CP A, E",
        {0xBB}
    },
    {
        "CP A, H",
        {0xBC}
    },
    {
        "CP A, L",
        {0xBD}
    },
    {
        "CP A, [HL]",
        {0xBE}
    },
    {
        "CP A, A",
        {0xBF}
    },
    {
        "RET NZ",
        {0xC0}
    },
    {
        "POP BC",
        {0xC1}
    },
    {
        "JP NZ, $ABCD",
        {0xC2, 0xCD, 0xAB}
    },
    {
        "JP $ABCD",
        {0xC3, 0xCD, 0xAB}
    },
    {
        "CALL NZ, $ABCD",
        {0xC4, 0xCD, 0xAB}
    },
    {
        "PUSH BC",
        {0xC5}
    },
    {
        "ADD A, 27",
        {0xC6, 0x1B}
    },
    {
        "RST $00",
        {0xC7}
    },
    {
        "RET Z",
        {0xC8}
    },
    {
        "RET ",
        {0xC9}
    },
    {
        "JP Z, $ABCD",
        {0xCA, 0xCD, 0xAB}
    },
    {
        "CALL Z, $ABCD",
        {0xCC, 0xCD, 0xAB}
    },
    {
        "CALL $ABCD",
        {0xCD, 0xCD, 0xAB}
    },
    {
        "ADC A, 27",
        {0xCE, 0x1B}
    },
    {
        "RST $08",
        {0xCF}
    },
    {
        "RET NC",
        {0xD0}
    },
    {
        "POP DE",
        {0xD1}
    },
    {
        "JP NC, $ABCD",
        {0xD2, 0xCD, 0xAB}
    },
    {
        "CALL NC, $ABCD",
        {0xD4, 0xCD, 0xAB}
    },
    {
        "PUSH DE",
        {0xD5}
    },
    {
        "SUB A, 27",
        {0xD6, 0x1B}
    },
    {
        "RST $10",
        {0xD7}
    },
    {
        "RET C",
        {0xD8}
    },
    {
        "RETI ",
        {0xD9}
    },
    {
        "JP C, $ABCD",
        {0xDA, 0xCD, 0xAB}
    },
    {
        "CALL C, $ABCD",
        {0xDC, 0xCD, 0xAB}
    },
    {
        "SBC A, 27",
        {0xDE, 0x1B}
    },
    {
        "RST $18",
        {0xDF}
    },
    {
        "LDH [27], A",
        {0xE0, 0x1B}
    },
    {
        "POP HL",
        {0xE1}
    },
    {
        "LD [C], A",
        {0xE2}
    },
    {
        "PUSH HL",
        {0xE5}
    },
    {
        "AND A, 27",
        {0xE6, 0x1B}
    },
    {
        "RST $20",
        {0xE7}
    },
    {
        "ADD SP, -27",
        {0xE8, 0xF9}
    },
    {
        "JP HL",
        {0xE9}
    },
    {
        "LD [$ABCD], A",
        {0xEA, 0xCD, 0xAB}
    },
    {
        "XOR A, 27",
        {0xEE, 0x1B}
    },
    {
        "RST $28",
        {0xEF}
    },
    {
        "LDH A, [27]",
        {0xF0, 0x1B}
    },
    {
        "POP AF",
        {0xF1}
    },
    {
        "LD A, [C]",
        {0xF2}
    },
    {
        "DI ",
        {0xF3}
    },
    {
        "PUSH AF",
        {0xF5}
    },
    {
        "OR A, 27",
        {0xF6, 0x1B}
    },
    {
        "RST $30",
        {0xF7}
    },
    {
        "LD HL, SP + -27",
        {0xF8, 0xF9}
    },
    {
        "LD SP, HL",
        {0xF9}
    },
    {
        "LD A, [$ABCD]",
        {0xFA, 0xCD, 0xAB}
    },
    {
        "EI ",
        {0xFB}
    },
    {
        "CP A, 27",
        {0xFE, 0x1B}
    },
    {
        "RST $38",
        {0xFF}
    },
};

#endif //GB_ASSEMBLER_GENERATEDTESTS_H