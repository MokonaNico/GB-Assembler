#ifndef GB_ASSEMBLER_TESTS_H
#define GB_ASSEMBLER_TESTS_H

#include <vector>
#include <cstdint>
#include "../src/Lexer.h"

void testAllBasicOperation();

struct OpTest {
    std::string op;
    std::vector<uint8_t> bin;
};

#endif //GB_ASSEMBLER_TESTS_H
