//
// Created by MokonaNico 20/08/2023.
//

#ifndef GB_ASSEMBLER_LEXER_HPP
#define GB_ASSEMBLER_LEXER_HPP

#include <vector>
#include <string>
#include <unordered_set>

enum class TokenType {
    // Operation tokens
    OPERATION,
    REGISTER16,
    REGISTER8,
    ADDRESS,
    CONDITION,
    NUMBER,
    // Label tokens
    LABEL,
    // Command tokens
    COMMAND,
    ARGUMENT,
    // Symbol tokens
    COMMA,
    RIGHT_BRACKET,
    LEFT_BRACKET,
    COLON,
    MINUS,
    PLUS,
    END_OF_FILE,
    NEWLINE,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(const std::string& sourceCode);
    Token getNextToken();
    static std::string tokenTypeToString(TokenType type);
private:
    const std::string& sourceCode;
    bool skipEmptyText();
    size_t position;
    bool lastTokenIsJump = false;
    std::unordered_set<std::string> operationList = {"LD","LDI","LDD","PUSH","POP",
                                                     "ADD","ADC","SUB","SBC","AND",
                                                     "XOR","OR","CP","INC","DEC","DAA",
                                                     "CPL","RLCA","RLA","RRCA","RRA",
                                                     "RLC","RL","RRC","RR","SLA","SWAP",
                                                     "SRA","SRL","BIT","SET","RES","CCF",
                                                     "SCF","NOP","HALT","STOP","DI","EI",
                                                     "JP","JR","CALL","RET","RETI","RST"};
    std::unordered_set<std::string> jumpList = {"JP", "JR", "CALL", "RET"};
    std::unordered_set<std::string> register16List = {"AF","BC","DE","HL","SP","PC"};
    std::unordered_set<std::string> register8List = {"A","B","C","D","E","H","L"};
    std::unordered_set<std::string> conditionList = {"NZ","Z","NC","C"};
};

#endif //GB_ASSEMBLER_LEXER_HPP
