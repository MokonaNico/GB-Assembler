//
// Created by MokonaNico 18/08/2023.
//

#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <any> 
#include <string>

enum class FlagType {
    INT,
    BOOL,
    STRING
};

struct FlagInfo {
    std::string flag;
    std::string short_flag;
    std::any default_value;
    std::string description;
    FlagType flagType;
};

class CommandLineParser {
public:
    void setProgramName(std::string name);
    void addFlag(const std::string& flag, const std::string& short_flag, const std::any& default_value,
                 const std::string& description, const FlagType& flagType);
    int parse(int argc, char* argv[]);
    void displayHelp();
    std::any getFlagValue(const std::string& flagName);

private:
    std::string programName_;
    std::vector<FlagInfo> flags_info;
    std::map<std::string, FlagInfo> flags_;
    std::map<std::string, std::any> values;
};

#endif // COMMAND_LINE_PARSER_H
