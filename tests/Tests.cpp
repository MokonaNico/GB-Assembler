#include <iostream>
#include <iomanip>
#include "Tests.h"
#include "../src/Assembler.h"
#include "GeneratedTests.h"

int main(int argc, char**argv){
    std::cout << "--- Begin testing ---" << std::endl;
    testAllBasicOperation();
    std::cout << "--- End testing ---" << std::endl;
}

void printBin(const std::vector<uint8_t>& bin){
    for (uint8_t element : bin) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(element) << " ";
    }
}

void printLex(const std::vector<Token>& tokens){
    for (const Token& tok : tokens) {
        std::cout << "<" << Lexer::tokenTypeToString(tok.type) << "," << tok.value << "> ";
    }
}

void testAllBasicOperation(){
    std::cout << "Testing all basics operations ... " << std::endl;

    int failedCount = 0;

    for (int i = 0; i < vectorTestGenerated.size(); i++){
        std::string op = vectorTestGenerated.at(i).op;

        // Test lexer
        Lexer lexer(op);
        Token token;
        std::vector<Token> tokens;
        token = lexer.getNextToken();
        while (token.type != TokenType::NEWLINE and token.type != TokenType::END_OF_FILE) {
            tokens.push_back(token);
            token = lexer.getNextToken();
        }
        // Test assembler
        Assembler assembler;
        std::vector<uint8_t> bin = assembler.generateBinaryInstruction(tokens);
        bool testAssembler = (bin == vectorTestGenerated.at(i).bin);

        if (not testAssembler) {
            failedCount++;
            std::cout << "[Failed] " << i << " - " << op << std::endl;
            std::cout << "     Expected Bin : ";
            printBin(vectorTestGenerated.at(i).bin);
            std::cout << std::endl;
            std::cout << "     Got          : ";
            printBin(bin);
            std::cout << std::endl;
        }
    }

    if (failedCount > 0)
        std::cout << "\nThere is " << failedCount << " test that failed." << std::endl;
    else
        std::cout << "All tests past successfully !" << std::endl;
}