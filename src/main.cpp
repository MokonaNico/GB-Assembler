#include <iostream>
#include <fstream>
#include <string>
#include "CommandLineParser.hpp"

int main(int argc, char**argv){
    CommandLineParser parser;
    parser.setProgramName("GB-Assembler");
    parser.addFlag("--input", "-i", "input.asm","The input file", CommandLineParser::FlagType::STRING);
    parser.addFlag("--output", "-o", "output.gb","The output file", CommandLineParser::FlagType::STRING);
    
    int res = parser.parse(argc, argv);
    if (res) return 0;

    std::cout << std::any_cast<char const *>(parser.getFlagValue("--input"));
    

    /*
    std::ifstream inputFile; 
    inputFile.open("input.asm");
    if (!inputFile.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier d'entrée." << std::endl;
        return 1;
    }

    inputFile.close();
    */

    return 0;
}
