//
// Created by mine- on 24/08/2023.
//

#include <iostream>
#include "Assembler.hpp"

std::vector<uint8_t> Assembler::generateBinaryInstruction(std::vector<Token> tokens) {
    for (const Token& token : tokens) {
        std::cout << "<" << Lexer::tokenTypeToString(token.type) << "," << token.value << "> ";
    }
    std::cout << std::endl;

    return std::vector<uint8_t>();
}
