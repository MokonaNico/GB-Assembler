#include <iostream>
#include <fstream>
#include <string>
#include "CommandLineParser.hpp"

int main(int argc, char**argv){
    CommandLineParser parser;
    parser.setProgramName("GB-Assembler");
    parser.addFlag("--input", "-i", std::string("input.asm"),
                   "The input file", CommandLineParser::FlagType::STRING);
    parser.addFlag("--output", "-o", std::string("output.gb"),
                   "The output file", CommandLineParser::FlagType::STRING);
    parser.addFlag("--aaa", "-a", false,
                   "test", CommandLineParser::FlagType::BOOL);
    parser.addFlag("--bbb", "-b", 27,
                   "test2", CommandLineParser::FlagType::INT);
    if (parser.parse(argc, argv)) return 0;

    std::cout << std::any_cast<std::string>(parser.getFlagValue("--input")) << std::endl;
    std::cout << std::any_cast<std::string>(parser.getFlagValue("--output")) << std::endl;
    std::cout << std::any_cast<bool>(parser.getFlagValue("--aaa")) << std::endl;
    std::cout << std::any_cast<int>(parser.getFlagValue("--bbb")) << std::endl;

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
