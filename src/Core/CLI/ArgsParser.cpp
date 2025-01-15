#include "Core/CLI/ArgsParser.h"
#include "tclap/ArgException.h"
#include "tclap/SwitchArg.h"
#include <iostream>
#include <string>
#include <tclap/Arg.h>

APROArgs::APROArgs(bool debug_mode){
    this -> debug_mode = debug_mode;
}

ArgsParser::ArgsParser(int args, char* argv[]) {
    _args = args;
    _argv = argv;
}

ArgsParser::~ArgsParser() {
    delete _argv;
}

APROArgs ArgsParser::parse(){
    try{
	TCLAP::CmdLine cmd("ASCII pro game engine CLI", ' ', "0.0.1");
	TCLAP::SwitchArg debug_arg("d", "debug-mode", "Run the game in debug mode", false);
	cmd.add(debug_arg);
	cmd.parse(_args, _argv);
	return APROArgs(debug_arg.getValue());
    } catch (TCLAP::ArgException &e){
	std::cout << "Failed to parse CLI Args" << e.what() << std::endl;
	throw e;
    }
}

