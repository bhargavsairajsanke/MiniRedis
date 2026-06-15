#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include <string>
#include <vector>

struct Command {
    std::string name;
    std::vector<std::string> args;
};

class CommandParser {
public:
    Command parse(const std::string& input) const;
};

#endif