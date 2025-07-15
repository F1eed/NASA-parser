#include <cassert>
#include <iostream>

#include "ArgParser.h"

int DigitToInt(char c) {
    // проверка на то, что пришедший символ - это реально цифра.
    assert(std::isdigit(c));
    return c - '0';
}

int StringToInt(char* str) {
    int result = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
      result = (result * 10 + DigitToInt(str[i]));
    }

    return result;
}

ParseOptions ParseArguments(int size,char *options[]){
  ParseOptions arguments;
  int i = 1;
  while (i < size){
    if (strcmp(options[i], "-o") == 0 || strcmp(options[i], "--output") == 0){
      if (i+1 < size){
        arguments.output_path = options[i+1];
        i++;
      }
    }
    else if(strncmp(options[i], "--output=", 9) == 0){
      char *fileName = options[i]+9;
      arguments.output_path = fileName;
    }
    else if((strncmp(options[i],"-o=", 3) == 0)){
      char *fileName = options[i]+3;
      arguments.output_path = fileName;
    }
    else if (strcmp(options[i], "-p") == 0 || strcmp(options[i], "--print") == 0){
      arguments.isPrintValue = true;
    }
    else if (strcmp(options[i], "-s") == 0 || strcmp(options[i], "--stats") == 0){
      arguments.isStatsValue = true;
      if (i+1 < size){
        arguments.statsValue = StringToInt(options[i+1]);
        i++;
      }
    }
    else if(strncmp(options[i], "--stats=", 8) == 0){
      arguments.isStatsValue = true;
      char *fileStats = options[i]+8;
      arguments.statsValue = StringToInt(fileStats);
    }
    else if((strncmp(options[i],"-s=", 3) == 0)){
      arguments.isStatsValue = true;
      char *fileStats = options[i]+3;
      arguments.statsValue = StringToInt(fileStats);
    }
    else if (strcmp(options[i], "-w") == 0 || strcmp(options[i], "--window") == 0){
      if (i+1 < size){
        arguments.windowTimeValue = StringToInt(options[i+1]);
        i++;
      }
    }
    else if(strncmp(options[i], "--window=", 9) == 0){
      char *fileWindowTime = options[i]+9;
      arguments.windowTimeValue = StringToInt(fileWindowTime);
    }
    else if((strncmp(options[i],"-w=", 3) == 0)){
      char *fileWindowTime = options[i]+3;
      arguments.windowTimeValue = StringToInt(fileWindowTime);
    }
    else if (strcmp(options[i], "-f") == 0 || strcmp(options[i], "--from") == 0){
      if (i+1 < size){
        arguments.fromTimeValue = StringToInt(options[i+1]);
        i++;
      }
    }
    else if(strncmp(options[i], "--from=", 7) == 0){
      char *FileName = options[i]+7;
      arguments.fromTimeValue = StringToInt(FileName);
    }
    else if((strncmp(options[i],"-f=", 3) == 0)){
      char *FileName = options[i]+3;
      arguments.fromTimeValue = StringToInt(FileName);
    }
    else if (strcmp(options[i], "-t") == 0 || strcmp(options[i], "--to") == 0){
      if (i+1 < size){
        arguments.toTimeValue = StringToInt(options[i+1]);
        i++;
      }
    }
    else if(strncmp(options[i], "--to=", 5) == 0){
      char *fileToTime = options[i]+5;
      arguments.toTimeValue = StringToInt(fileToTime);
    }
    else if((strncmp(options[i],"-t=", 3) == 0)){
      char *fileFromTime = options[i]+3;
      arguments.toTimeValue = StringToInt(fileFromTime);
    }
    else{
      arguments.inputFile = options[i];
    }
    i++;
  }
  return arguments;
}
