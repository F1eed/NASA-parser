#include <iostream>

#include "ArgParser.h"
#include "lib/Helpers/Helpers.h"

Options parseArguments(int size, char* options[]){
  Options arguments;
  int i = 1;
  while (i < size){
    if (strcmp(options[i], "-o") == 0 || strcmp(options[i], "--output") == 0){
      if (i+1 < size){
        arguments.outputPath = options[i+1];
        i++;
      }
    }
    else if(strncmp(options[i], "--output=", 9) == 0){
      char* fileName = options[i]+9;
      arguments.outputPath = fileName;
    }
    else if((strncmp(options[i],"-o=", 3) == 0)){
      char* fileName = options[i]+3;
      arguments.outputPath = fileName;
    }
    else if (strcmp(options[i], "-p") == 0 || strcmp(options[i], "--print") == 0){
      arguments.isPrintValue = true;
    }
    else if (strcmp(options[i], "-s") == 0 || strcmp(options[i], "--stats") == 0){
      arguments.isStatsValue = true;
      if (i+1 < size){
        std::string fileStats = options[i+1];
        arguments.statsValue = StringToInt(fileStats);
        i++;
      }
    }
    else if(strncmp(options[i], "--stats=", 8) == 0){
      arguments.isStatsValue = true;
      std::string fileStats = options[i]+8;
      arguments.statsValue = StringToInt(fileStats);
    }
    else if((strncmp(options[i],"-s=", 3) == 0)){
      arguments.isStatsValue = true;
      std::string fileStats = options[i]+3;
      arguments.statsValue = StringToInt(fileStats);
    }
    else if (strcmp(options[i], "-w") == 0 || strcmp(options[i], "--window") == 0){
      if (i+1 < size){
        std::string fileWindowTime = options[i+1];
        arguments.windowTimeValue = StringToInt(fileWindowTime);
        i++;
      }
    }
    else if(strncmp(options[i], "--window=", 9) == 0){
      std::string fileWindowTime = options[i]+9;
      arguments.windowTimeValue = StringToInt(fileWindowTime);
    }
    else if((strncmp(options[i],"-w=", 3) == 0)){
      std::string fileWindowTime = options[i]+3;
      arguments.windowTimeValue = StringToInt(fileWindowTime);
    }
    else if (strcmp(options[i], "-f") == 0 || strcmp(options[i], "--from") == 0){
      if (i+1 < size){
        std::string fileFromTime = options[i+1];
        arguments.fromTimeValue = StringToInt(fileFromTime);
        i++;
      }
    }
    else if(strncmp(options[i], "--from=", 7) == 0){
      std::string fileFromTime = options[i]+7;
      arguments.fromTimeValue = StringToInt(fileFromTime);
    }
    else if((strncmp(options[i],"-f=", 3) == 0)){
      std::string fileFromTime = options[i]+3;
      arguments.fromTimeValue = StringToInt(fileFromTime);
    }
    else if (strcmp(options[i], "-t") == 0 || strcmp(options[i], "--to") == 0){
      if (i+1 < size){
        std::string fileToTime = options[i+1];
        arguments.toTimeValue = StringToInt(fileToTime);
        i++;
      }
    }
    else if(strncmp(options[i], "--to=", 5) == 0){
      std::string fileToTime = options[i]+5;
      arguments.toTimeValue = StringToInt(fileToTime);
    }
    else if((strncmp(options[i],"-t=", 3) == 0)){
      std::string fileToTime = options[i]+3;
      arguments.toTimeValue = StringToInt(fileToTime);
    }
    else{
      arguments.inputFile = options[i];
    }
    i++;
  }
  return arguments;
}
