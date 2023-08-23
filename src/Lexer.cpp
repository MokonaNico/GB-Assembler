//
// Created by MokonaNico on 20/08/2023.
//

#include <iostream>
#include "Lexer.hpp"

Lexer::Lexer(const std::string& sourceCode) : sourceCode(sourceCode), position(0) {}

Token Lexer::getNextToken() {
    if(skipEmptyText()){
        return {TokenType::END_OF_FILE, ""};
    }

    // Else we parse the char
    char currentChar = sourceCode[position];
    position++;

    // handle comment
    while (currentChar == ';'){
        currentChar = sourceCode[position++];
        // Now skip everything and stop when end of the document or end of the line
        while(position < sourceCode.length() and currentChar != '\n'){
            currentChar = sourceCode[position++];
        }

        if(skipEmptyText()){
            return {TokenType::END_OF_FILE, ""};
        }

        currentChar = sourceCode[position];
        position++;
    }

    if (std::isalpha(currentChar)){
        // Need to check if it's a label, an instruction or a register
        // Label are easy to find because they always end with :


    }


    // MAYBE USELESS AND CAN BE DELETED
    if (currentChar == '\n') {
        return {TokenType::NEWLINE, ""};
    }

    return {TokenType::UNKNOWN, std::string(1, currentChar)};
}

std::string Lexer::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::OPERATION: return "OPERATION";
        case TokenType::REGISTER: return "REGISTER";
        case TokenType::ADDRESS: return "ADDRESS";
        case TokenType::VALUE: return "VALUE";
        case TokenType::LABEL: return "LABEL";
        case TokenType::COMMAND: return "COMMAND";
        case TokenType::ARGUMENT: return "ARGUMENT";
        case TokenType::COMA: return "COMA";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::COLON: return "COLON";
        case TokenType::PICSOU: return "PICSOU";
        case TokenType::NEWLINE: return "NEWLINE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

bool Lexer::skipEmptyText() {
    // Go to the next char or the end of the file
    while(position < sourceCode.length() && std::isspace(sourceCode[position])) {
        position += 1;
    }

    // Here we have to check if it's the case where we are at the end of the file
    if (position >= sourceCode.length()) {
        return true;
    } else {
        return false;
    }
}

