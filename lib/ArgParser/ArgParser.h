#pragma once

struct Options {
  std::string outputPath = "";
  bool isPrintValue = false;
  int statsValue = 10;
  int windowTimeValue = 0;
  long long fromTimeValue = 0;
  long long toTimeValue = LLONG_MAX;
  std::string inputFile = "";
  bool isStatsValue = false;
};

Options parseArguments(int size,char *options[]);
