#include "CommandLineParser.hpp"
#include <iostream>


void CommandLineParser::setProgramName(std::string name) {
    programName_ = name;
}

void CommandLineParser::addFlag(std::string flag, std::string short_flag, std::any default_value, std::string description, FlagType flagType) {
    FlagInfo flagInfo = {flag, short_flag, default_value, description, flagType};
    values[flag] = default_value;
    flags_info.push_back(flagInfo);
    flags_[flagInfo.flag] = flagInfo;
    flags_[flagInfo.short_flag] = flagInfo;
}

int CommandLineParser::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            displayHelp();
            return 1;
        } else if (flags_.count(arg)){
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                values[arg] = argv[i + 1];
                i++;
            } else {
                std::cerr << "Flag " << arg << " requires a value." << std::endl;
                displayHelp();
                return 1;
            }
        } else {
            std::cerr << "Unknown argument: " << arg << std::endl;
            displayHelp();
            return 1;
        }
    }
    return 0;
}

void CommandLineParser::displayHelp() {
    std::cout << "Usage: " << programName_ << " [flags]" << std::endl;
    std::cout << "Flags:" << std::endl;
    for (const FlagInfo& flagInfo : flags_info) {
        std::cout << " / " << flagInfo.flag;
        std::cout << "  " << flagInfo.short_flag;

        std::cout << " (default: ";
        
        if (flagInfo.flagType == FlagType::INT){
            std::cout << std::any_cast<int>(flagInfo.default_value) << " INT";
        } else if (flagInfo.flagType == FlagType::BOOL){
            std::cout << std::any_cast<bool>(flagInfo.default_value) << " BOOL";
        } else if (flagInfo.flagType == FlagType::STRING){
            std::cout << std::any_cast<char const *>(flagInfo.default_value) << " STRING";
        } 
        std::cout << ")";

        std::cout << "\t" << flagInfo.description << std::endl;
    }
}

std::any CommandLineParser::getFlagValue(const std::string flagName){
    return values[flagName];
}