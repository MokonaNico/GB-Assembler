//
// Created by MokonaNico on 24/08/2023.
//

#include <iostream>
#include <sstream>
#include "Assembler.hpp"

#define CAST(var) static_cast<uint8_t>(var)

std::vector<uint8_t> Assembler::generateBinaryInstruction(std::vector<Token> tokens) {
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
    if (operation == "EI"   and tokens.size() == 1) return {0xFB};
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
    if (checkOp(tokens,{OP,R8}))
        reg = register8Bits.at(tokens[1].value);
    else if (checkOp(tokens, {OP,LBR,R16,RBR}) and tokens[2].value == "HL")
        reg = 0x06;
    else if (checkOp(tokens, {OP,NUM,COM,R8})){
        num = static_cast<uint8_t>(std::stoi(tokens[1].value)) << 3;
        reg = register8Bits.at(tokens[3].value);
    } else if (checkOp(tokens, {OP,NUM,COM,LBR,R16,RBR}) and tokens[3].value == "HL"){
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
    std::string operation = tokens[0].value;

    // ADD,ADC,SUB,SBC,AND,XOR,OR,CP
    if (arithmeticOpMap.find(operation) != arithmeticOpMap.end()){
        uint8_t baseAddress = arithmeticOpMap.at(operation);
        if (checkOp(tokens, {OP,R8,COM,R8}))
            return {CAST(baseAddress + register8Bits.at(tokens[3].value))};
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and tokens[4].value == "HL")
            return {CAST(baseAddress + 0x06)};
        if (checkOp(tokens, {OP,R8,COM,NUM}))
            return {CAST(baseAddress + 0x46), getByteFromString(tokens[3].value)};
    }

    // Specific case of ADD
    if (operation == "ADD") {
        if (checkOp(tokens, {OP,R16,COM,R16}) and tokens[1].value == "HL")
            return {CAST(0x09 + register16Bits.at(tokens[3].value))};
        if (checkOp(tokens, {OP,R8,COM,NUM}) and tokens[1].value == "A")
            return {0xC6, getByteFromString(tokens[3].value)};
        if (checkOp(tokens, {OP,R16,COM,NUM}) and tokens[1].value == "SP")
            return {0xE8, getByteFromString(tokens[3].value)};
    }

    // INC,DEC
    if (arithmeticAltOpMap.find(operation) != arithmeticAltOpMap.end()){
        uint8_t baseAddress = arithmeticAltOpMap.at(operation);
        if (checkOp(tokens, {OP,R8}))
            return {CAST(baseAddress + register8BitsAlt.at(tokens[1].value))};
        if (checkOp(tokens, {OP,LBR,R16,RBR}) and tokens[2].value == "HL")
            return {CAST(baseAddress + 0x30)};
        if (checkOp(tokens, {OP,R16})){
            return {CAST(arithmeticAlt16OpMap.at(operation) + register16Bits.at(tokens[1].value))};
        }
    }
    throw std::runtime_error("Unknown operation.");
}

std::vector<uint8_t> Assembler::handlerLoadOperation(std::vector<Token> tokens) {
    std::string operation = tokens[0].value;

    if (operation == "LD"){
        // 0x40 -> 0x7F (not 0x76)
        if (checkOp(tokens, {OP,R8,COM,R8})){
            uint8_t lowerBits = register8Bits.at(tokens[3].value);
            uint8_t midBits = register8Bits.at(tokens[1].value) << 3;
            return {CAST(0x40 + midBits + lowerBits)};
        }
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and (tokens[4].value == "HL" or tokens[4].value == "HLI")){
            uint8_t midBits = register8Bits.at(tokens[1].value) << 3;
            return {CAST(0x46 + midBits)};
        }
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[2].value == "HL"){
            uint8_t lowerBits = register8Bits.at(tokens[5].value);
            return {CAST(0x70 + lowerBits)};
        }

        // 0x01 0x11 0x21 0x31
        if (checkOp(tokens, {OP,R16,COM,NUM}))
            return {CAST(0x01 + register16Bits.at(tokens[1].value)),
                    getByteFromString(tokens[3].value),
                    getUpperByteFromString(tokens[3].value)};

        // 0x02 0x12 0x22 0x32
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[5].value == "A"){
            if (tokens[2].value == "BC") return {0x02};
            if (tokens[2].value == "DE") return {0x12};
        }
        if (checkOp(tokens, {OP,LBR,R16,PLU,RBR,COM,R8}) and tokens[2].value == "HL" and tokens[6].value == "A")
            return {0x22};
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[2].value == "HLI" and tokens[5].value == "A")
            return {0x22};
        if (checkOp(tokens, {OP,LBR,R16,MIN,RBR,COM,R8}) and tokens[2].value == "HL" and tokens[6].value == "A")
            return {0x32};
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[2].value == "HLD" and tokens[5].value == "A")
            return {0x32};

        // 0x06 0x16 0x26 0x36
        if (checkOp(tokens, {OP,R8,COM,NUM}))
            return {register8BitsLoad.at(tokens[1].value), getByteFromString(tokens[3].value)};
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,NUM}))
            return {0x36, getByteFromString(tokens[5].value)};

        // 0x0A 0x1A 0x2A 0x3A
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and tokens[1].value == "A"){
            if (tokens[4].value == "BC") return {0x0A};
            if (tokens[4].value == "DE") return {0x1A};
        }
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,PLU,RBR}) and tokens[1].value == "A" and tokens[4].value == "HL")
            return {0x2A};
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,MIN,RBR}) and tokens[1].value == "A" and tokens[4].value == "HL")
            return {0x3A};
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and tokens[1].value == "A" and tokens[4].value == "HLD")
            return {0x3A};


        // 0x08
        if (checkOp(tokens, {OP,LBR,NUM,RBR,COM,R16}) and tokens[5].value == "SP")
            return {0x08,
                    getByteFromString(tokens[2].value),
                    getUpperByteFromString(tokens[2].value)};

        // 0xE2 0xF2
        if (checkOp(tokens, {OP,LBR,R8,RBR,COM,R8}) and tokens[2].value == "C" and tokens[5].value == "A")
            return {0xE2};
        if (checkOp(tokens, {OP,LBR,NUM,PLU,R8,RBR,COM,R8}) and
           tokens[2].value == "65280" and tokens[4].value == "C" and tokens[7].value == "A")
            return {0xE2};
        if (checkOp(tokens, {OP,R8,COM,LBR,R8,RBR}) and tokens[1].value == "A" and tokens[4].value == "C")
            return {0xF2};
        if (checkOp(tokens, {OP,R8,COM,LBR,NUM,PLU,R8,RBR}) and
            tokens[1].value == "A" and tokens[4].value == "65280" and tokens[6].value == "C")
            return {0xF2};

        // 0xF8
        if (checkOp(tokens, {OP,R16,COM,R16,PLU,NUM}) and tokens[1].value == "HL" and tokens[3].value == "SP")
            return {0xF8, getByteFromString(tokens[5].value)};

        // 0xF9
        if (checkOp(tokens, {OP,R16,COM,R16}) and tokens[1].value == "SP" and tokens[3].value == "HL")
            return {0xF9};

        // 0xEA
        if (checkOp(tokens, {OP,LBR,NUM,RBR,COM,R8}) and tokens[5].value == "A")
            return {0xEA,
                    getByteFromString(tokens[2].value),
                    getUpperByteFromString(tokens[2].value)};

        // 0xFA
        if (checkOp(tokens, {OP,R8,COM,LBR,NUM,RBR}) and tokens[1].value == "A")
            return {0xFA,
                    getByteFromString(tokens[4].value),
                    getUpperByteFromString(tokens[4].value)};
        //0xE0
        if (checkOp(tokens, {OP,LBR,NUM,PLU,NUM,RBR,COM,R8}) and
            tokens[2].value == "65280" and tokens[7].value == "A")
            return {0xE0, getByteFromString(tokens[4].value)};
        //0xF0
        if (checkOp(tokens, {OP,R8,COM,LBR,NUM,PLU,NUM,RBR}) and
            tokens[1].value == "A" and tokens[4].value == "65280")
            return {0xF0, getByteFromString(tokens[6].value)};
    }

    if (operation == "LDH"){
        //0xE0
        if (checkOp(tokens, {OP,LBR,NUM,RBR,COM,R8}) and tokens[5].value == "A")
            return {0xE0, getByteFromString(tokens[2].value)};
        //0xF0
        if (checkOp(tokens, {OP,R8,COM,LBR,NUM,RBR}) and tokens[1].value == "A")
            return {0xF0, getByteFromString(tokens[4].value)};
    }

    if (operation == "LDI"){
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and tokens[4].value == "HL"){
            uint8_t midBits = register8Bits.at(tokens[1].value) << 3;
            return {CAST(0x46 + midBits)};
        }
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[2].value == "HL" and tokens[5].value == "A")
            return {0x22};
    }

    if (operation == "LDD"){
        if (checkOp(tokens, {OP,R8,COM,LBR,R16,RBR}) and tokens[1].value == "A" and tokens[4].value == "HL")
            return {0x3A};
        if (checkOp(tokens, {OP,LBR,R16,RBR,COM,R8}) and tokens[2].value == "HL" and tokens[5].value == "A")
            return {0x3A};
    }

    if (operation == "LDHL"){
        if (checkOp(tokens, {OP,R16,COM,NUM}) and tokens[1].value == "SP")
            return {0xF8, getByteFromString(tokens[3].value)};
    }

    if (operation == "POP" and checkOp(tokens,{OP,R16}))
        return {CAST(0xC1 + register16BitsStack.at(tokens[1].value))};

    if (operation == "PUSH" and checkOp(tokens, {OP,R16}))
        return {CAST(0xC5 + register16BitsStack.at(tokens[1].value))};

    throw std::runtime_error("Unknown operation.");
}

std::vector<uint8_t> Assembler::handlerJumpOperation(std::vector<Token> tokens) {
    std::string operation = tokens[0].value;
    if (operation == "JR"){
        if (checkOp(tokens, {OP,NUM}))
            return {0x18, getByteFromString(tokens[1].value)};
        if (checkOp(tokens, {OP,COND,COM,NUM})){
            uint8_t num = getByteFromString(tokens[3].value);
            return {CAST(0x20 + conditionBits.at(tokens[1].value)), num};
        }
    }

    if (operation == "JP"){
        if (checkOp(tokens, {OP,NUM}))
            return {0xC3, getByteFromString(tokens[1].value),
                          getUpperByteFromString(tokens[1].value)};
        if (checkOp(tokens, {OP,COND,COM,NUM})) {
            uint8_t up_add = getByteFromString(tokens[3].value);
            uint8_t low_add = getUpperByteFromString(tokens[3].value);
            return {CAST(0xC2 + conditionBits.at(tokens[1].value)), up_add, low_add};
        }
        if (checkOp(tokens, {OP, R16}))
            return {0xE9};
    }

    if (operation == "RET"){
        if (checkOp(tokens, {OP})) return {0xC9};
        if (checkOp(tokens, {OP, COND}))
            return {CAST(0xC0 + conditionBits.at(tokens[1].value))};
    }

    if (operation == "RETI" and tokens.size() == 1)
        return {0xD9};

    if (operation == "CALL"){
        if (checkOp(tokens, {OP,NUM}))
            return {0xCD, getByteFromString(tokens[1].value),
                          getUpperByteFromString(tokens[1].value)};
        if (checkOp(tokens, {OP,COND,COM,NUM})) {
            uint8_t up_add = getByteFromString(tokens[3].value);
            uint8_t low_add = getUpperByteFromString(tokens[3].value);
            return {CAST(0xC4 + conditionBits.at(tokens[1].value)), up_add, low_add};
        }
    }

    if (operation == "RST" and checkOp(tokens, {OP,NUM})){
        return {CAST(0xC7 + rstAddBits.at(tokens[1].value))};
    }

    throw std::runtime_error("Unknown operation.");
}

uint8_t Assembler::getByteFromString(const std::string& number) {
    return static_cast<uint8_t>(std::stoi(number));
}

uint8_t Assembler::getUpperByteFromString(const std::string &number) {
    return static_cast<uint8_t>(std::stoi(number) >> 8);
}

bool Assembler::checkOp(std::vector<Token> tokens, std::vector<TokenType> expected) {
    if (tokens.size() != expected.size()) return false;
    for (int i = 0; i < tokens.size(); i++){
        if (tokens[i].type != expected[i]) return false;
    }
    return true;
}

