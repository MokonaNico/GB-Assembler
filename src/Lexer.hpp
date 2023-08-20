//
// Created by mine- on 20/08/2023.
//

#ifndef GB_ASSEMBLER_LEXER_HPP
#define GB_ASSEMBLER_LEXER_HPP

#include <vector>
#include <string>

class Lexer {
public:
    enum TokenType {
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
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    std::vector<Token> tokenizeText(std::vector<std::string> text);
};


#endif //GB_ASSEMBLER_LEXER_HPP
