#include <iostream>
#include "lib/ArgParser/ArgParser.h"
#include "lib/FileParser/FileParser.h"

int main(int argc, char *argv[]) {
    ParseOptions arguments = ParseArguments(argc, argv);
    if (arguments.inputFile != ""){
        Parse(arguments);
    }
    else{
        std::printf("Usage: AnalyzeLog [OPTIONS] logs_filename\n");
    }
    return 0;
}
