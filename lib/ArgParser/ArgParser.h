#pragma once

struct ParseOptions {
  std::string output_path = "";
  bool isPrintValue = false;
  int statsValue = 10;
  int windowTimeValue = 0;
  int fromTimeValue = 0;
  int toTimeValue = 0;
  std::string inputFile = "";
  bool isStatsValue = false;
};
int DigitToInt(char c);
int StringToInt(char* str);
ParseOptions ParseArguments(int size,char *options[]);
