//
// Created by MokonaNico on 24/08/2023.
//

#ifndef GB_ASSEMBLER_ASSEMBLER_HPP
#define GB_ASSEMBLER_ASSEMBLER_HPP


#include <cstdint>
#include <vector>
#include <map>
#include "Lexer.hpp"

class Assembler {
public:
    std::vector<uint8_t> generateBinaryInstruction(std::vector<Token> tokens);
private:
    std::vector<uint8_t> handlerOperation(std::vector<Token> tokens);
    std::vector<uint8_t> handlerOperationReg(std::vector<Token> tokens, uint8_t baseAddress);
    std::vector<uint8_t> handlerOperationRegAlt(std::vector<Token> tokens, uint8_t baseAddress);
    std::vector<uint8_t> handlerRegisterNumber(std::vector<Token> tokens, uint8_t operation);

    // Prefix
    std::vector<uint8_t> handlerPrefixedOperation(std::vector<Token> tokens);
    std::map<std::string, uint8_t> prefixedOpMap = {
            {"RLC", 0x00},
            {"RRC", 0x08},
            {"RL",  0x10},
            {"RR",  0x18},
            {"SLA", 0x20},
            {"SRA", 0x28},
            {"SWAP",0x30},
            {"SRL", 0x38},
            {"BIT", 0x40},
            {"RES", 0x80},
            {"SET", 0xC0}
    };
    std::map<std::string, uint8_t> register8Bits = {
            {"B", 0x00},
            {"C", 0x01},
            {"D", 0x02},
            {"E", 0x03},
            {"H", 0x04},
            {"L", 0x05},
            {"A", 0x07}
    };

    std::map<std::string, uint8_t> register16Bits = {
            {"BC", 0x00},
            {"DE", 0x10},
            {"HL", 0x20},
            {"SP", 0x30}
    };
    std::map<std::string, uint8_t> arithmeticOpMap = {
            {"ADD",  0x80},
            {"ADC",  0x88},
            {"SUB",  0x90},
            {"SBC",  0x98},
            {"AND",  0xA0},
            {"XOR",  0xA8},
            {"OR",   0xB0},
            {"CP",   0xB8},
    };

    std::map<std::string, uint8_t> arithmeticAltOpMap = {
            {"INC",  0x04},
            {"DEC",  0x05},
    };
    std::map<std::string, uint8_t> arithmeticAlt16OpMap = {
            {"INC",  0x03},
            {"DEC",  0x0B},
    };
    std::map<std::string, uint8_t> register8BitsAlt = {
            {"B", 0x00},
            {"C", 0x08},
            {"D", 0x10},
            {"E", 0x18},
            {"H", 0x20},
            {"L", 0x28},
            {"A", 0x38}
    };
};

#endif //GB_ASSEMBLER_ASSEMBLER_HPP
