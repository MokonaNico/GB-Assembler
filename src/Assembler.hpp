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

    std::vector<uint8_t> handlerArithmeticOperation(std::vector<Token> tokens);
    std::unordered_set<std::string> arithmeticOpList = {"ADD","ADC","SUB","SBC","AND","XOR","OR",
                                                        "CP","INC","DEC"};
    std::vector<uint8_t> handlerLoadOperation(std::vector<Token> tokens);
    std::unordered_set<std::string> loadOpList = {"LD","LDH","POP","PUSH"};
    std::vector<uint8_t> handlerJumpOperation(std::vector<Token> tokens);
    std::unordered_set<std::string> jumpOpList = {"JP","JR","RET","CALL","RST","RETI"};

    static uint8_t getByteFromString(const std::string& number);
    static uint8_t getUpperByteFromString(const std::string& number);
    static uint8_t getByteFromAddressString(const std::string& address);
    static uint8_t getUpperByteFromAddressString(const std::string& address);

    static bool checkOp(std::vector<Token> tokens, std::vector<TokenType> expected);

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
    std::map<std::string, uint8_t> register16BitsStack = {
            {"BC", 0x00},
            {"DE", 0x10},
            {"HL", 0x20},
            {"AF", 0x30}
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
    std::map<std::string, uint8_t> register8BitsLoad = {
            {"B", 0x06},
            {"C", 0x0E},
            {"D", 0x16},
            {"E", 0x1E},
            {"H", 0x26},
            {"L", 0x2E},
            {"A", 0x3E}
    };
    std::map<std::string, uint8_t> conditionBits = {
            {"NZ", 0x00},
            {"Z",  0x08},
            {"NC", 0x10},
            {"C",  0x18}
    };
    std::map<std::string, uint8_t> rstAddBits = {
            {"00", 0x00},
            {"08", 0x08},
            {"10", 0x10},
            {"18", 0x18},
            {"20", 0x20},
            {"28", 0x28},
            {"30", 0x30},
            {"38", 0x38}
    };
};

#endif //GB_ASSEMBLER_ASSEMBLER_HPP
