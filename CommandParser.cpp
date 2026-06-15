#include "CommandParser.h"

#include <sstream>
#include <cctype>

using namespace std;

static string toUpper(const string& str) {
    string result = str;

    for (char& ch : result)
        ch = toupper(static_cast<unsigned char>(ch));

    return result;
}

Command CommandParser::parse(const string& input) const {
    Command cmd;
    string token;
    stringstream ss(input);

    if (ss >> token)
        cmd.name = toUpper(token);

    while (ss >> token)
        cmd.args.push_back(token);

    return cmd;
}