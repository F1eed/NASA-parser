#include <iostream>
#include <fstream>
#include "lib/ArgParser/ArgParser.h"
#include "lib/FileParser/FileParser.h"

int main(int argc, char *argv[]) {
    Options arguments = parseArguments(argc, argv);
    if (arguments.inputFile != ""){
        std::ifstream logsFile(arguments.inputFile);
        if (arguments.outputPath != "") {
            std::ofstream outputFile(arguments.outputPath + ".log");
        }
        std::ofstream outputFile("output.log");
        checkOutputFile(outputFile);
        ProcessLogs(logsFile, outputFile, arguments);
    }
    else{
        std::printf("Usage: AnalyzeLog [OPTIONS] logs_filename");
    }
    return 0;
}
