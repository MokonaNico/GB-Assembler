//
// Created by mine- on 24/08/2023.
//

#ifndef GB_ASSEMBLER_ASSEMBLER_HPP
#define GB_ASSEMBLER_ASSEMBLER_HPP


#include <cstdint>
#include <vector>
#include "Lexer.hpp"

class Assembler {
public:
    std::vector<uint8_t> generateBinaryInstruction(std::vector<Token> tokens);
};

#endif //GB_ASSEMBLER_ASSEMBLER_HPP
