//
// Created by MokonaNico on 24/08/2023.
//

#include <iostream>
#include "Assembler.hpp"

std::vector<uint8_t> Assembler::generateBinaryInstruction(std::vector<Token> tokens) {

    // TODO : Delete this print
    for (const Token& token : tokens) {
        std::cout << "<" << Lexer::tokenTypeToString(token.type) << "," << token.value << "> ";
    }
    std::cout << std::endl;

    if (tokens[0].type == TokenType::OPERATION) return handlerOperation(tokens);
    
    throw std::runtime_error("Unknown operation.");
}

std::vector<uint8_t> Assembler::handlerOperation(std::vector<Token> tokens) {
    std::string operation = tokens[0].value;

    // Misc / control instructions
    if (operation == "NOP"  and tokens.size() == 1) return {0x00};
    if (operation == "STOP" and tokens.size() == 1) return {0x10,0x00};
    if (operation == "HALT" and tokens.size() == 1) return {0x76};
    if (operation == "DI"   and tokens.size() == 1) return {0xF3};
    if (operation == "EI"   and tokens.size() == 1) return {0xFA};
    if (operation == "CCF"  and tokens.size() == 1) return {0x3F};
    if (operation == "SCF"  and tokens.size() == 1) return {0x37};

    // Shift, rotate and bit instructions (prefixed operation)
    if (operation == "RLCA" and tokens.size() == 1) return {0x07};
    if (operation == "RLA"  and tokens.size() == 1) return {0x17};
    if (operation == "RRCA" and tokens.size() == 1) return {0x0F};
    if (operation == "RRA"  and tokens.size() == 1) return {0x1F};
    if (prefixedOpList.find(operation) != prefixedOpList.end() and tokens.size() >= 2)
        return handlerPrefixedOperation(tokens);

    throw std::runtime_error("Unknown operation.");
}

/***/

std::vector<uint8_t> Assembler::handlerPrefixedOperation(std::vector<Token> tokens) {
    /**
     * Since prefixed operation table is a bit more organized than the operation table,
     * we can easily build the binary
     *
     * In fact :
     *  - The 3 lower bits indicate the register/address in this order (B,C,D,E,H,L,[HL],A)
     *  - The 5 upper bits indicate the operation
     *  - The BIT,RES,SET are order by value or argument
     */

    std::string operation = tokens[0].value;

    // Variable for the register/address and number value argument
    // These are going to be added to make the full opcode
    uint8_t reg = 0;
    uint8_t num = 0;

    // We need to find if it's a register, an address or a number
    // In the case of a number, it means that we are in BIT,RES or SET
    // So we check the second argument
    if (tokens[1].type == TokenType::REGISTER8)
        reg = prefixedArgMap.at(tokens[1].value);
    else if (tokens[1].type == TokenType::LEFT_BRACKET and
             tokens[2].value == "HL" and
             tokens[3].type == TokenType::RIGHT_BRACKET )
        reg = 0x06;
    else if (tokens[1].type == TokenType::NUMBER){
        num = static_cast<uint8_t>(std::stoi(tokens[1].value)) << 3;
        if (tokens[3].type == TokenType::REGISTER8)
            reg = prefixedArgMap.at(tokens[3].value);
        else if (tokens[3].type == TokenType::LEFT_BRACKET)
            reg = 0x06;
    }
    else throw std::runtime_error("Unknown operation.");

    // Add the value to make the final opcode
    uint8_t out = prefixedOpMap[operation] + reg + num;
    return {0xCB, out};
}

