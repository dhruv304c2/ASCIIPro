#ifndef ARGSPARSER_H
#define ARGSPARSER_H

#include <tclap/CmdLine.h>

class APROArgs{
public:
    bool debug_mode;
    APROArgs(bool debugMode);
};

class ArgsParser {
public:
    ArgsParser(int args, char* argv[]);
    ~ArgsParser();
    APROArgs parse();
private:
    int _args;
    char** _argv;
};

#endif
