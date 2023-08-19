#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <string>
#include <vector>
#include <map>
#include <any> 
#include <string>

class CommandLineParser {
public:
    enum FlagType {
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

    void setProgramName(std::string name);
    void addFlag(std::string flag, std::string short_flag, std::any default_value, std::string description, FlagType flagType);
    int parse(int argc, char* argv[]);
    void displayHelp();
    std::any getFlagValue(std::string flagName);

private:
    std::string programName_;
    std::vector<FlagInfo> flags_info;
    std::map<std::string, FlagInfo> flags_;
    std::map<std::string, std::any> values;
};

#endif // COMMAND_LINE_PARSER_H
