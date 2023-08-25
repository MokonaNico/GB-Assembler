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


    // Prefix
    std::vector<uint8_t> handlerPrefixedOperation(std::vector<Token> tokens);
    std::unordered_set<std::string> prefixedOpList = {"RLC","RRC","RL","RR","SLA","SRA",
                                                      "SWAP","SRL","BIT","RES","SET"};
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
    std::map<std::string, uint8_t> prefixedArgMap = {
            {"B", 0x00},
            {"C", 0x01},
            {"D", 0x02},
            {"E", 0x03},
            {"H", 0x04},
            {"L", 0x05},
            {"A", 0x07}
    };
};

#endif //GB_ASSEMBLER_ASSEMBLER_HPP
