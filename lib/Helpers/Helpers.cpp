#include <cassert>
#include <iostream>
#include "Helpers.h"

int DigitToInt(char c) {
  if (!std::isdigit(c)) {
    return 0;
  };
  return c - '0';
}

int StringToInt(const std::string& str) {
    int result = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
      result = (result * 10 + DigitToInt(str[i]));
    }

    return result;
}