//
// Created by MokonaNico 18/08/2023.
//

#include "CommandLineParser.hpp"
#include <iostream>
#include <utility>

/**
 * Set the name of the program for the display help
 * @param name the name of the program
 */
void CommandLineParser::setProgramName(std::string name) {
    programName_ = std::move(name);
}

/**
 * Add a flag to be parsed
 * @param flag the flag long version like : --input
 * @param short_flag the flag short version like : -i
 * @param default_value the default value, need to match up with the flagType (for string need std::string)
 * @param description a short description of the parameters of the flag
 * @param flagType the value type of the flag
 */
void CommandLineParser::addFlag(const std::string& flag,const std::string& short_flag, const std::any& default_value,
                                const std::string& description, const FlagType& flagType) {
    FlagInfo flagInfo = {flag, short_flag, default_value, description, flagType};
    values[flag] = default_value; // already fill values with default and if the flag is present it will override this value
    flags_info.push_back(flagInfo); // for display help
    // add flag and short flag to the map, so it's easy to find the flagInfo with either one
    flags_[flagInfo.flag] = flagInfo;
    flags_[flagInfo.short_flag] = flagInfo;
}

/**
 * Parse the argument of the command
 * @param argc it's supposed to be the argc from the main
 * @param argv it's supposed to be the argv from the main
 * @return if display help then return 1, otherwise return 0
 * suppose to stop the program if the value is 1
 */
int CommandLineParser::parse(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++){
        std::string arg = argv[i];

        // Check if help or version before to continue
        if (arg == "--help" || arg == "-h") {
            displayHelp();
            return 1;
        } else if (arg == "--version" || arg == "-v"){
            std::cout << "GB-Assembler version 0.1";
            return 1;
        }

        // If the argument is not a flag, then it's an unknown argument, and we stop
        if (!flags_.count(arg)){
            std::cout << "Unknown argument: " << arg << std::endl;
            displayHelp();
            return 1;
        }

        const FlagInfo& flagInfo = flags_[arg];

        // If the flag is a bool, then we don't need the value after, and it becomes true
        if (flagInfo.flagType == FlagType::BOOL) {
            values[flagInfo.flag] = true;
            continue;
        }

        // If it's not a bool then we need the value after exist and to not be a parameter
        // note: the - is supposed to check if it's a parameter or not
        // note: it implies that an INT can't be negative (at least it doesn't handle this case for not)
        if (i + 1 < argc && argv[i + 1][0] != '-') {
            std::string argValue = argv[i + 1];
            std::any value;
            if (flagInfo.flagType == FlagType::INT) {
                value = std::stoi(argValue);
            } else if (flagInfo.flagType == FlagType::STRING) {
                value = argValue;
            }
            values[flagInfo.flag] = value;
            i++;
        } else {
            std::cout << "Flag " << arg << " requires a value." << std::endl;
            displayHelp();
            return 1;
        }
    }
    return 0;
}

/**
 * Display the help menu
 */
void CommandLineParser::displayHelp() {
    std::cout << "Usage: " << programName_ << " [flags]" << std::endl;
    std::cout << "Flags:" << std::endl;
    for (const FlagInfo& flagInfo : flags_info) {
        std::cout << " / " << flagInfo.flag << "  " << flagInfo.short_flag;

        std::cout << " (default: ";
        // need to cast the std::any, so we do that with the help of the flag type
        if (flagInfo.flagType == FlagType::INT)
            std::cout << std::any_cast<int>(flagInfo.default_value) << " INT";
        else if (flagInfo.flagType == FlagType::BOOL)
            std::cout << std::any_cast<bool>(flagInfo.default_value) << " BOOL";
        else if (flagInfo.flagType == FlagType::STRING)
            std::cout << std::any_cast<std::string>(flagInfo.default_value) << " STRING";
        std::cout << ")";

        std::cout << "\t Description : " << flagInfo.description << std::endl;
    }
}

/**
 * Return the value of a certain flag
 * @param flagName the flag name (the long version with --)
 * @return the value as a std::any, use the FlagType to do an any_cast
 */
std::any CommandLineParser::getFlagValue(const std::string& flagName){
    return values[flagName];
}