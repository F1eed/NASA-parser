#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <algorithm>

#include "lib/ArgParser/ArgParser.h"
#include "lib/Helpers/Helpers.h"

const int MIN_SIZE_OF_NORMAL_LOG = 9;

struct Log {
    std::string remoteAddr;
    long long localTime;
    std::string request;
    uint16_t status;
    int bytesSend; 
};

void checkOutputFile(std::ofstream& outputFile) {
    if (!outputFile.is_open()) {
        std::cerr << "\033[31mERROR: failed to open output file\033[0m\n";
        exit(1);
    }
}

void print(std::ofstream& outputFile, std::string& logLine, bool needPrinted) {
    if (needPrinted){
        std::cout << logLine << "\n";
    }
    if (outputFile.is_open()){
        outputFile << logLine + "\n";
    }
}

std::string Merge(std::string& firstString, std::string& secondString) {
    return firstString + " " + secondString;
}

std::vector<std::string> Split(const std::string& str, char sep) {
    std::vector<std::string> result;
    bool needToAdd = true;

    for (auto c : str) {
        if (c == sep) {
            needToAdd = true;
        } else {
            if (needToAdd) {
                result.push_back("");
                needToAdd = false;
            }

            result.back().push_back(c);
        }
    }

    return result;
}

long long ToUnix(const std::string& datetime) {
    std::istringstream ss(datetime);
    std::tm tm;

    ss >> std::get_time(&tm, "%d/%b/%Y:%H:%M:%S %z");
    
    return std::mktime(&tm);
}

Log parseLogTokens(std::vector<std::string>& tokens) {
    Log splittedLog;

    splittedLog.remoteAddr = tokens[0];
    tokens[3] = tokens[3].substr(1);
    tokens[4] = tokens[4].substr(0, tokens[4].size()-1);

    splittedLog.localTime = ToUnix(Merge(tokens[3], tokens[4]));

    splittedLog.bytesSend = StringToInt(tokens.back());
    splittedLog.status = StringToInt(tokens[tokens.size() - 2]);

    for(int i = 5; i < tokens.size() - 3; ++i) {
        splittedLog.request += tokens[i] + " ";
    }
    splittedLog.request += tokens[tokens.size() - 3];
    
    return splittedLog;
}

void ProcessLogs (std::ifstream& in, std::ofstream& out, Options& options) {
    std::string logLine = "";
    std::deque<std::pair<long long, std::string>> window;

    std::unordered_map <std::string, int> requestWithServerErrorStatus;
    long long maxWindowSize = 0;
    std::string startWindow = "";
    std::string endWindow = "";
    std::vector <std::string> serverErrorLogs;

    while (std::getline(in, logLine)) {
        std::vector<std::string> tokens = Split(logLine, ' ');
        if (tokens.size() < MIN_SIZE_OF_NORMAL_LOG) {
            continue;
        }
        Log parsedLog = parseLogTokens(tokens);

        if (!(options.fromTimeValue <= parsedLog.localTime && parsedLog.localTime <= options.toTimeValue)) continue;

        if (options.windowTimeValue) {
            window.push_back({parsedLog.localTime, logLine});
            while (!window.empty() && window.back().first - window.front().first > options.windowTimeValue) {
                window.pop_front();
            }

            if (window.size() > maxWindowSize) {
                maxWindowSize = window.size();
                startWindow = window.front().second;
                endWindow = window.back().second;
            }
        }

        if (parsedLog.status >= 500) {
            serverErrorLogs.push_back(logLine);
            if (options.isStatsValue) {
                requestWithServerErrorStatus[parsedLog.request]++;
            }
            print(out, logLine, options.isPrintValue);
        }
    }


    if (options.windowTimeValue) {
        std::cout << "Max Requests in " << options.windowTimeValue << " seconds is " << maxWindowSize << "\nStarting at: " << startWindow << "\nEnding at: " << endWindow << "\n";
    }

    if (options.isStatsValue) {
        auto cmp = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        };
        
        std::vector<std::pair<std::string, int>> v(requestWithServerErrorStatus.begin(), requestWithServerErrorStatus.end());
        std::sort(v.begin(), v.end(), cmp);

        for(int i = 0; i < std::min(options.statsValue, static_cast<int>(v.size())); ++i) {
            std::cout << v[i].second << ": " << v[i].first << "\n";
        }
    }
}
