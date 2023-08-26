//
// Created by MokonaNico on 24/08/2023.
//

#include <iostream>
#include "Assembler.hpp"

#define CAST(var) static_cast<uint8_t>(var)


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
    if (prefixedOpMap.find(operation) != prefixedOpMap.end() and tokens.size() >= 2)
        return handlerPrefixedOperation(tokens);

    // Arithmetic instructions
    if (operation == "CPL" and tokens.size() == 1) return {0x2F};
    if (operation == "CCF" and tokens.size() == 1) return {0x3F};
    if (operation == "DAA" and tokens.size() == 1) return {0x27};
    if (operation == "SCF" and tokens.size() == 1) return {0x37};
    if (arithmeticOpList.find(operation) != arithmeticOpList.end())
        return handlerArithmeticOperation(tokens);

    // Load instructions
    if (loadOpList.find(operation) != loadOpList.end())
        return handlerLoadOperation(tokens);

    // Jumps/calls instructions
    if (jumpOpList.find(operation) != jumpOpList.end())
        return handlerJumpOperation(tokens);

    throw std::runtime_error("Unknown operation.");
}

/***/

/**
 * Handler for the prefixed operation
 * Since prefixed operation table is a bit more organized than the operation table,
 * we can easily build the binary
 *
 * In fact :
 *  - The 3 lower bits indicate the register/address in this order (B,C,D,E,H,L,[HL],A)
 *  - The 5 upper bits indicate the operation
 *  - The BIT,RES,SET are order by value or argument
 *
 * @param tokens vector of tokens
 * @return vector of bytes
 */
std::vector<uint8_t> Assembler::handlerPrefixedOperation(std::vector<Token> tokens) {
    std::string operation = tokens[0].value;

    // Variable for the register/address and number value argument
    // These are going to be added to make the full opcode
    uint8_t reg = 0;
    uint8_t num = 0;

    // We need to find if it's a register, an address or a number
    // In the case of a number, it means that we are in BIT,RES or SET
    // So we check the second argument
    if (isOpReg8(tokens))
        reg = register8Bits.at(tokens[1].value);
    else if (isOpBrReg16Br(tokens) and tokens[2].value == "HL")
        reg = 0x06;
    else if (isOpNumReg8(tokens)){
        num = static_cast<uint8_t>(std::stoi(tokens[1].value)) << 3;
        reg = register8Bits.at(tokens[3].value);
    } else if (isOpNumBrReg16Br(tokens) and tokens[3].value == "HL"){
        num = static_cast<uint8_t>(std::stoi(tokens[1].value)) << 3;
        reg = 0x06;
    } else throw std::runtime_error("Unknown operation.");

    // Add the value to make the final opcode
    uint8_t out = prefixedOpMap[operation] + reg + num;
    return {0xCB, out};
}

/**
 * Handler for the arithmetic operations
 * @param tokens vector of tokens
 * @return vector of bytes
 */
std::vector<uint8_t> Assembler::handlerArithmeticOperation(std::vector<Token> tokens) {
    // TODO : Support arithmetic instruction without register A (ADD A,B -> ADD B)
    std::string operation = tokens[0].value;

    // ADD,ADC,SUB,SBC,AND,XOR,OR,CP
    if (arithmeticOpMap.find(operation) != arithmeticOpMap.end()){
        uint8_t baseAddress = arithmeticOpMap.at(operation);
        if (isOpReg8Reg8(tokens))
            return {CAST(baseAddress + register8Bits.at(tokens[3].value))};
        if (isOpReg8BrReg16Br(tokens) and tokens[4].value == "HL")
            return {CAST(baseAddress + 0x06)};
        if (isOpReg8Number(tokens))
            return {CAST(arithmeticOpMap.at(operation) + 0x46),
                    getByteFromString(tokens[3].value)};
    }

    // Specific case of ADD
    if (operation == "ADD") {
        if (isOpReg16Reg16(tokens) and tokens[1].value == "HL")
            return {CAST(0x09 + register16Bits.at(tokens[3].value))};
        if (isOpReg8Number(tokens) and tokens[1].value == "A")
            return {0xC6, getByteFromString(tokens[3].value)};
        if (isOpReg16Number(tokens) and tokens[1].value == "SP")
            return {0xE8, getByteFromString(tokens[3].value)};
    }

    // INC,DEC
    if (arithmeticAltOpMap.find(operation) != arithmeticAltOpMap.end()){
        uint8_t baseAddress = arithmeticAltOpMap.at(operation);
        if (isOpReg8(tokens))
            return {CAST(baseAddress + register8BitsAlt.at(tokens[1].value))};
        if (isOpBrReg16Br(tokens) and tokens[2].value == "HL")
            return {CAST(baseAddress + 0x30)};
        if (isOpReg16(tokens)){
            return {CAST(arithmeticAlt16OpMap.at(operation) + register16Bits.at(tokens[1].value))};
        }
    }
    throw std::runtime_error("Unknown operation.");
}

std::vector<uint8_t> Assembler::handlerLoadOperation(std::vector<Token> tokens) {
    std::string operation = tokens[0].value;

    if (operation == "LD"){
        if (isOpReg16Number(tokens))
            return {CAST(0x01 + register16Bits.at(tokens[1].value)),
                    getByteFromString(tokens[3].value),
                    getUpperByteFromString(tokens[3].value)};

        if (isOpBrReg16BrReg8(tokens) and tokens[5].value == "A"){
            if (tokens[2].value == "BC") return {0x02};
            if (tokens[2].value == "DE") return {0x12};
        }
        if (isOpBrReg16PlusBrReg8(tokens) and tokens[2].value == "HL" and tokens[6].value == "A")
            return {0x22};
        if (isOpBrReg16MinusBrReg8(tokens) and tokens[2].value == "HL" and tokens[6].value == "A")
            return {0x32};

        if (isOpReg8Number(tokens))
            return {register8BitsLoad.at(tokens[1].value), getByteFromString(tokens[3].value)};
        if (isOpBrReg16BrNumber(tokens))
            return {0x36, getByteFromString(tokens[5].value)};

        if (isOpReg8BrReg16Br(tokens) and tokens[1].value == "A"){
            if (tokens[4].value == "BC") return {0x0A};
            if (tokens[4].value == "DE") return {0x1A};
        }


    }

    throw std::runtime_error("Unknown operation.");
}

std::vector<uint8_t> Assembler::handlerJumpOperation(std::vector<Token> tokens) {
    throw std::runtime_error("Unknown operation.");
}









uint8_t Assembler::getByteFromString(const std::string& number) {
    return static_cast<uint8_t>(std::stoi(number));
}

uint8_t Assembler::getUpperByteFromString(const std::string &number) {
    return static_cast<uint8_t>(std::stoi(number) >> 8);
}





bool Assembler::isOpReg8(std::vector<Token> tokens) {
    if (tokens.size() != 2) return false;
    return tokens[1].type == TokenType::REGISTER8;
}

bool Assembler::isOpReg16(std::vector<Token> tokens) {
    if (tokens.size() != 2) return false;
    return tokens[1].type == TokenType::REGISTER16;
}

bool Assembler::isOpBrReg16Br(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::LEFT_BRACKET and
           tokens[2].type == TokenType::REGISTER16 and
           tokens[3].type == TokenType::RIGHT_BRACKET;
}

bool Assembler::isOpNumReg8(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::NUMBER and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::REGISTER8;
}

bool Assembler::isOpNumBrReg16Br(std::vector<Token> tokens) {
    if (tokens.size() != 6) return false;
    return tokens[1].type == TokenType::NUMBER and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::LEFT_BRACKET and
           tokens[4].type == TokenType::REGISTER16 and
           tokens[5].type == TokenType::RIGHT_BRACKET;
}

bool Assembler::isOpReg8Reg8(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::REGISTER8 and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::REGISTER8;
}

bool Assembler::isOpReg8BrReg16Br(std::vector<Token> tokens) {
    if (tokens.size() != 6) return false;
    return tokens[1].type == TokenType::REGISTER8 and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::LEFT_BRACKET and
           tokens[4].type == TokenType::REGISTER16 and
           tokens[5].type == TokenType::RIGHT_BRACKET;
}

bool Assembler::isOpReg8Number(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::REGISTER8 and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::NUMBER;
}

bool Assembler::isOpReg16Reg16(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::REGISTER16 and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::REGISTER16;
}

bool Assembler::isOpReg16Number(std::vector<Token> tokens) {
    if (tokens.size() != 4) return false;
    return tokens[1].type == TokenType::REGISTER16 and
           tokens[2].type == TokenType::COMMA and
           tokens[3].type == TokenType::NUMBER;
}

bool Assembler::isOpBrReg16BrReg8(std::vector<Token> tokens) {
    if (tokens.size() != 6) return false;
    return tokens[1].type == TokenType::LEFT_BRACKET and
           tokens[2].type == TokenType::REGISTER16 and
           tokens[3].type == TokenType::RIGHT_BRACKET and
           tokens[4].type == TokenType::COMMA and
           tokens[5].type == TokenType::REGISTER8;
}

bool Assembler::isOpBrReg16PlusBrReg8(std::vector<Token> tokens) {
    if (tokens.size() != 7) return false;
    return tokens[1].type == TokenType::LEFT_BRACKET and
           tokens[2].type == TokenType::REGISTER16 and
           tokens[3].type == TokenType::PLUS and
           tokens[4].type == TokenType::RIGHT_BRACKET and
           tokens[5].type == TokenType::COMMA and
           tokens[6].type == TokenType::REGISTER8;
}

bool Assembler::isOpBrReg16MinusBrReg8(std::vector<Token> tokens) {
    if (tokens.size() != 7) return false;
    return tokens[1].type == TokenType::LEFT_BRACKET and
           tokens[2].type == TokenType::REGISTER16 and
           tokens[3].type == TokenType::MINUS and
           tokens[4].type == TokenType::RIGHT_BRACKET and
           tokens[5].type == TokenType::COMMA and
           tokens[6].type == TokenType::REGISTER8;
}

bool Assembler::isOpBrReg16BrNumber(std::vector<Token> tokens) {
    if (tokens.size() != 6) return false;
    return tokens[1].type == TokenType::LEFT_BRACKET and
           tokens[2].type == TokenType::REGISTER16 and
           tokens[3].type == TokenType::RIGHT_BRACKET and
           tokens[4].type == TokenType::COMMA and
           tokens[5].type == TokenType::NUMBER;
}







