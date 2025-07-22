#include <iostream>
#include <fstream>
#include "lib/ArgParser/ArgParser.h"
#include "lib/FileParser/FileParser.h"

// вынести логику из GetArguments, тут убрать такую проверку, поставить в другом месте с проверкой на пустоту и с проверкой на открытие файла сразу

int main(int argc, char *argv[]) {
    Options arguments = parseArguments(argc, argv);
    if (arguments.inputFile != ""){
        std::ifstream logsFile(arguments.inputFile);
        std::ofstream outputFile(arguments.outputPath + ".log");
        checkOutputFile(outputFile);
        ProcessLogs(logsFile, outputFile, arguments);
    }
    else{
        std::printf("Usage: AnalyzeLog [OPTIONS] logs_filename");
    }
    return 0;
}
