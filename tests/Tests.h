#ifndef GB_ASSEMBLER_TESTS_H
#define GB_ASSEMBLER_TESTS_H

#include <vector>
#include <cstdint>
#include "../src/Lexer.hpp"

void testAllBasicOperation();

struct OpTest {
    std::string op;
    std::vector<Token> tokens;
    std::vector<uint8_t> bin;
};

std::vector<OpTest> vectorOpTest= {
        {"NOP", {{OP, "NOP"}},{0x00}},

        {"LD BC,$ABCD", {
            {OP,"LD"},
            {R16,"BC"},
            {COM,","},
            {NUM, "43981"}},
                {0x01,0xCD,0xAB}},

        {"LD [BC], A", {
            {OP,"LD"},
            {LBR, "["},
            {R16, "BC"},
            {RBR, "]"},
            {COM, ","},
            {R8, "A"}},
                {0x02}},

        {"INC BC", {
            {OP, "INC"},
            {R16, "BC"}},
                {0x03}},

        {"INC B", {
                           {OP, "INC"},
                           {R8, "B"}},
                {0x04}},

        {"DEC B", {
                           {OP, "DEC"},
                           {R8, "B"}},
                {0x05}},

        {"LD B, 27", {
                           {OP, "LD"},
                           {R8, "B"},
                           {COM, ","},
                           {NUM, "27"}},
                {0x06,0x1B}},

        {"RLCA", {{OP, "RLCA"}},{0x07}},

        {"LD [$ABCD], SP", {
                {OP, "LD"},
                {LBR, "["},
                {NUM, "43981"},
                {RBR, "]"},
                {COM, ","},
                {R16, "SP"}},
         {0x08,0xCD,0xAB}},

        {"ADD HL, BC", {
                {OP, "ADD"},
                {R16, "HL"},
                {COM, ","},
                {R16, "BC"}},
         {0x09}},

        {"LD A, [BC]", {
                {OP, "LD"},
                {R8, "A"},
                {COM, ","},
                {LBR, "["},
                {R16, "BC"},
                {RBR, "]"}},
         {0x0A}},

        {"DEC BC", {
                {OP, "DEC"},
                {R16, "BC"}},
         {0x0B}},

        {"INC C", {
                {OP, "INC"},
                {R8, "C"}},
         {0x0C}},

        {"DEC C", {
                {OP, "DEC"},
                {R8, "C"}},
         {0x0D}},

        {"LD C, 27", {
                {OP, "LD"},
                {R8, "C"},
                {COM, ","},
                {NUM, "27"}},
         {0x0E,0x1B}},

        {"RRCA", {{OP, "RRCA"}},{0x0F}}
};

#endif //GB_ASSEMBLER_TESTS_H
