#pragma once

struct Log;

void checkOutputFile(std::ofstream& outputFile);

void print(std::ofstream& outputFile, std::string& logLine, bool needPrinted);

std::string Merge(std::string& firstString, std::string& secondString);

std::vector<std::string> Split(const std::string& str, char sep);

long long ToUnix(const std::string& datetime);

Log parseLogTokens(std::vector<std::string>& tokens);

void ProcessLogs (std::ifstream& in, std::ofstream& out, Options& options);
