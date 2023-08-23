//
// Created by MokonaNico 18/08/2023.
//

#include <iostream>
#include <fstream>
#include <string>
#include "CommandLineParser.hpp"
#include "Lexer.hpp"

int main(int argc, char**argv){
    CommandLineParser parser;
    parser.setProgramName("GB-Assembler");
    parser.addFlag("--input", "-i", std::string("input.asm"),
                   "The input file", CommandLineParser::FlagType::STRING);
    parser.addFlag("--output", "-o", std::string("output.gb"),
                   "The output file", CommandLineParser::FlagType::STRING);
    if (parser.parse(argc, argv)) return 0;

    auto input_filename = std::any_cast<std::string>(parser.getFlagValue("--input"));
    auto output_filename = std::any_cast<std::string>(parser.getFlagValue("--output"));

    std::ifstream inputFile; 
    inputFile.open(input_filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error while trying to open the input file." << std::endl;
        return 1;
    }

    std::string sourceCode;
    std::string line;
    while (std::getline(inputFile, line)) {
        sourceCode += line + "\n";
    }

    Lexer lexer(sourceCode);

    Token token;
    do {
        token = lexer.getNextToken();
        std::cout << "Token type: " << Lexer::tokenTypeToString(token.type) << ", Value: " << token.value << std::endl;
    } while (token.type != TokenType::END_OF_FILE);




    std::ofstream outputFile;
    outputFile.open(output_filename, std::ios::out | std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error while trying to create the output file." << std::endl;
        return 1;
    }

    /*
    std::vector<uint8_t> hexVector = {0xFF, 0x00, 0xAA, 0x55};
    for(uint8_t value : hexVector)
        outputFile.put((char) value);
    */

    outputFile.close();
    inputFile.close();
    return 0;
}
