//
// Created by MokonaNico on 20/08/2023.
//

#include <iostream>
#include "Lexer.hpp"

/**
 * Constructor of the Lexer class
 * @param sourceCode the assembly source code
 */
Lexer::Lexer(const std::string& sourceCode) : sourceCode(sourceCode), position(0) {}

/**
 * Parse the source code and return the current next token
 * @return the next token
 */
Token Lexer::getNextToken() {
    if(skipEmptyText()){
        return {TokenType::END_OF_FILE, ""};
    }

    // we parse the char
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

    // Handle the case where we have alpha char, it means that we can be in one of these token type :
    // - Operation
    // - Condition
    // - Register
    // - Label
    // So we need to check in which case we are
    if (std::isalpha(currentChar)){
        // First we get the whole word
        std::string word;
        word += currentChar;
        currentChar = sourceCode[position];
        while (std::isalnum(currentChar) || currentChar == '_'){
            word += currentChar;
            position++;
            currentChar = sourceCode[position];
        }

        // Then we check if the word is in some word list to find is type
        if (operationList.find(word) != operationList.end()) {
            // Need to note that it's a jump op because we need this information for the condition token
            lastTokenIsJump = (jumpList.find(word) != jumpList.end());
            return {TokenType::OPERATION, word};
        } else if (conditionList.find(word) != conditionList.end() and lastTokenIsJump) {
            return {TokenType::CONDITION, word};
        } else if (register16List.find(word) != register16List.end()){
            return {TokenType::REGISTER16, word};
        } else if (register8List.find(word) != register8List.end()){
            return {TokenType::REGISTER8, word};
        } else {
            // We say that by default, it's a label
            return {TokenType::LABEL, word};
        }
    }

    // If it's a digit, then it's going to be a number token
    // We just need to parse the digit entirely
    if (std::isdigit(currentChar) or (currentChar == '-' and std::isdigit(sourceCode[position]))){
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

    // If it begins with a dot, it's a command token, we skip the dot and parse the command name
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

    // If it's a $, then it's a number write-in hexadecimal. We already convert this number
    // in base 10.
    if (currentChar == '$'){
        // parse the hex number
        std::string hexNumber;
        currentChar = sourceCode[position];
        while(std::isxdigit(currentChar)){
            hexNumber += currentChar;
            position++;
            currentChar = sourceCode[position];
        }

        // transform the hex number into a base10 number
        int decimalValue = std::stoi(hexNumber, nullptr, 16);

        return {TokenType::NUMBER, std::to_string(decimalValue)};
    }

    // Token for some special character
    if (currentChar == ',') return {TokenType::COMMA, ","};
    if (currentChar == ':') return {TokenType::COLON, ":"};
    if (currentChar == '[' or currentChar == '(') return {TokenType::LEFT_BRACKET, "["};
    if (currentChar == ']' or currentChar == ')') return {TokenType::RIGHT_BRACKET, "]"};
    if (currentChar == '-') return {TokenType::MINUS, "-"};
    if (currentChar == '+') return {TokenType::PLUS, "+"};
    if (currentChar == '\n') return {TokenType::NEWLINE, ""};

    // If it doesn't fall in any-case, then it's an unknown token
    // (maybe throw an error when this token is returned)
    return {TokenType::UNKNOWN, std::string(1, currentChar)};
}

/**
 * Return a string for the enum TokenType
 * @param type the TokenType
 * @return a string that represent the TokenType value
 */
std::string Lexer::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::OPERATION: return "OPERATION";
        case TokenType::REGISTER16: return "REGISTER16";
        case TokenType::REGISTER8: return "REGISTER8";
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

/**
 * Helper method to easily skip empty text
 * @return true if it's the end of the file, false either
 */
bool Lexer::skipEmptyText() {
    // Go to the next char or the end of the file
    while(position < sourceCode.length() && sourceCode[position] != '\n' && std::isspace(sourceCode[position])) {
        position += 1;
    }

    // Here we have to check if it's the case where we are at the end of the file
    return (position >= sourceCode.length());
}

