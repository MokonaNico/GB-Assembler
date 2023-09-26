#include <iostream>
#include "Tests.h"
#include "../src/Assembler.hpp"

int main(int argc, char**argv){
    std::cout << "--- Begin testing ---" << std::endl;
    testAllBasicOperation();
    std::cout << "--- End testing ---" << std::endl;
}

void testAllBasicOperation(){
    std::cout << "Testing all basics operations : " << std::endl;

    for (int i = 0; i < vectorOpTest.size(); i++){
        std::string op = vectorOpTest.at(i).op;

        // Test lexer
        Lexer lexer(op);
        Token token;
        std::vector<Token> tokens;
        token = lexer.getNextToken();
        while (token.type != TokenType::NEWLINE and token.type != TokenType::END_OF_FILE) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }
        bool testLexer = (tokens == vectorOpTest.at(i).tokens);

        // Test assembler
        Assembler assembler;
        std::vector<uint8_t> bin = assembler.generateBinaryInstruction(tokens);
        bool testAssembler = (bin == vectorOpTest.at(i).bin);

        std::cout << "[" << testLexer << testAssembler << "] " << i << " - " << op << std::endl;
    }


}