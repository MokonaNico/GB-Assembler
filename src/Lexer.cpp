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
    }

    if (std::isalpha(currentChar)){
        // Need to check if it's a label, an instruction or a register
        // Label are easy to find because they always end with :
        std::string word;
        word += currentChar;
        currentChar = sourceCode[position];
        while (std::isalnum(currentChar) || currentChar == '_'){
            word += currentChar;
            position++;
            currentChar = sourceCode[position];
        }

        if (operationList.find(word) != operationList.end()) {
            lastTokenIsJump = (jumpList.find(word) != jumpList.end());
            return {TokenType::OPERATION, word};
        } else if (conditionList.find(word) != conditionList.end() and lastTokenIsJump) {
            return {TokenType::CONDITION, word};
        } else if (register16List.find(word) != register16List.end()){
            return {TokenType::REGISTER16, word};
        } else if (register8List.find(word) != register8List.end()){
            return {TokenType::REGISTER8, word};
        } else {
            return {TokenType::LABEL, word};
        }
    }

    if (std::isdigit(currentChar)){
        std::string number;
        number += currentChar;
        currentChar = sourceCode[position];
        while (std::isdigit(currentChar)){
            number += currentChar;
            position++;
            currentChar = sourceCode[position];
        }
        return {TokenType::NUMBER, number};
    }

    if (currentChar == '.'){
        // Command
        std::string command;
        currentChar = sourceCode[position];
        while(std::isalpha(currentChar)){
            command += currentChar;
            position++;
            currentChar = sourceCode[position];
        }
        return {TokenType::COMMAND, command};
    }

    if (currentChar == '$'){
        // address
        std::string address;
        currentChar = sourceCode[position];
        while(std::isxdigit(currentChar)){
            address += currentChar;
            position++;
            currentChar = sourceCode[position];
        }
        return {TokenType::ADDRESS, address};
    }

    if (currentChar == ','){
        return {TokenType::COMMA, ","};
    }

    if (currentChar == ':'){
        return {TokenType::COLON, ":"};
    }

    if (currentChar == '[' or currentChar == '('){
        return {TokenType::LEFT_BRACKET, "["};
    }

    if (currentChar == ']' or currentChar == ')'){
        return {TokenType::RIGHT_BRACKET, "]"};
    }

    if (currentChar == '-'){
        return {TokenType::MINUS, "-"};
    }

    if (currentChar == '+'){
        return {TokenType::PLUS, "+"};
    }

    if (currentChar == '\n'){
        return {TokenType::NEWLINE, ""};
    }

    return {TokenType::UNKNOWN, std::string(1, currentChar)};
}

std::string Lexer::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::OPERATION: return "OPERATION";
        case TokenType::REGISTER16: return "REGISTER16";
        case TokenType::REGISTER8: return "REGISTER8";
        case TokenType::ADDRESS: return "ADDRESS";
        case TokenType::CONDITION: return "CONDITION";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::LABEL: return "LABEL";
        case TokenType::COMMAND: return "COMMAND";
        case TokenType::ARGUMENT: return "ARGUMENT";
        case TokenType::COMMA: return "COMMA";
        case TokenType::RIGHT_BRACKET: return "RIGHT_BRACKET";
        case TokenType::LEFT_BRACKET: return "LEFT_BRACKET";
        case TokenType::COLON: return "COLON";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::NEWLINE: return "NEWLINE";
        case TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "ERROR";
    }
}

bool Lexer::skipEmptyText() {
    // Go to the next char or the end of the file
    while(position < sourceCode.length() && sourceCode[position] != '\n' && std::isspace(sourceCode[position])) {
        position += 1;
    }

    // Here we have to check if it's the case where we are at the end of the file
    if (position >= sourceCode.length()) {
        return true;
    } else {
        return false;
    }
}

