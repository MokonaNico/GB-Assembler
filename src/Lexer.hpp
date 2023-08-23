//
// Created by MokonaNico 20/08/2023.
//

#ifndef GB_ASSEMBLER_LEXER_HPP
#define GB_ASSEMBLER_LEXER_HPP

#include <vector>
#include <string>

enum class TokenType {
    // Operation tokens
    OPERATION,
    REGISTER,
    ADDRESS,
    VALUE,
    // Label tokens
    LABEL,
    // Command tokens
    COMMAND,
    ARGUMENT,
    // Symbol tokens
    COMA,
    RIGHT_BRACKET,
    LEFT_BRACKET,
    COLON,
    PICSOU,
    NEWLINE,
    END_OF_FILE,
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
};

#endif //GB_ASSEMBLER_LEXER_HPP
