#include <cstdio>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

#include "lib/ArgParser/ArgParser.h"

struct LogData{
    std::string ip = "";
    std::string datetime = "";
    std::string request = "";
    std::string statusCode = "";
    std::string bytesSend = "";
};

std::string Merge(std::string& firstString, std::string& secondString){
    std::string temp = firstString + " " + secondString;
    return temp;
}


std::vector<std::string> Split(const std::string& Logs, char sep) {
    std::vector<std::string> result;
    bool needToAdd = true;

    for (auto c : Logs) {
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

long long ToUnix(const std::string& datetime){
    std::istringstream ss(datetime);
    std::tm tm;

    ss >> std::get_time(&tm, "%d/%b/%Y:%H:%M:%S %z");
    long long timestamp = std::mktime(&tm);
    
    return timestamp;
}


void Parse(ParseOptions arg) {
    std::string filename = "../../" + arg.inputFile;
    std::ifstream LogsFile(filename);
    std::string buffer;
    std::vector <std::string> serverErrorLogs;
    if (arg.output_path != "") {
        arg.output_path = "../../" + arg.output_path;
    }
    std::ofstream file(arg.output_path);
    std::map <std::string, int> requestWithServerErrorStatus;
    if (arg.toTimeValue == 0){
        if (arg.windowTimeValue != 0) {
            long long maxRequestSize = 0;
            std::vector <long long> requests;
            while (std::getline(LogsFile, buffer)) {
                std::vector <std::string> splitLog = Split(buffer, ' ');
                LogData splittedLog;
                splittedLog.ip = splitLog[0];
                splitLog[3] = splitLog[3].substr(1, splitLog[3].size());
                splitLog[4] = splitLog[4].substr(0, splitLog[4].size()-1);
                splitLog[5] = splitLog[5].substr(1, splitLog[5].size());
                if (splitLog[7] == "HTTP/1.0\"") {
                    splitLog[7] = splitLog[7].substr(0, splitLog[7].size()-1);
                    splittedLog.request  = Merge(splitLog[5], splitLog[6]);
                    splittedLog.request = Merge(splittedLog.request, splitLog[7]);
                    splittedLog.statusCode = splitLog[8];
                    splittedLog.bytesSend = splitLog[9];
                }
                else {
                    splittedLog.request = Merge(splitLog[5],splitLog[6]);
                    splittedLog.statusCode = splitLog[7];
                    splittedLog.bytesSend = splitLog[8];
                }
                splittedLog.datetime = Merge(splitLog[3], splitLog[4]);
                long long unixTime = ToUnix(splittedLog.datetime);
                requests.push_back(unixTime);
                if (requests[requests.size() -1] - requests[0] > arg.windowTimeValue){
                    if (requests.size()-1 > maxRequestSize){
                        maxRequestSize = requests.size()-1;
                    }
                    requests.erase(requests.begin());
                }
                if (unixTime >= arg.fromTimeValue){
                    if (splittedLog.statusCode[0] == '5'){
                        if (arg.isStatsValue){
                            requestWithServerErrorStatus[splittedLog.request] ++;
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                        else{
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                    }
                }
            }
            if (requests[requests.size() -1] - requests[0] <= arg.windowTimeValue){
                if (requests.size() > maxRequestSize){
                    maxRequestSize = requests.size();
                }
                requests.erase(requests.begin());
            }
            std::cout << "Max Requests in " << arg.windowTimeValue << " seconds is " << maxRequestSize << "\n";
        }   
        else{
            while (std::getline(LogsFile, buffer)) {
                std::vector <std::string> splitLog = Split(buffer, ' ');
                LogData splittedLog;
                splittedLog.ip = splitLog[0];
                splitLog[3] = splitLog[3].substr(1, splitLog[3].size());
                splitLog[4] = splitLog[4].substr(0, splitLog[4].size()-1);
                splitLog[5] = splitLog[5].substr(1, splitLog[5].size());
                if (splitLog[7] == "HTTP/1.0\"") {
                    splitLog[7] = splitLog[7].substr(0, splitLog[7].size()-1);
                    splittedLog.request  = Merge(splitLog[5], splitLog[6]);
                    splittedLog.request = Merge(splittedLog.request, splitLog[7]);
                    splittedLog.statusCode = splitLog[8];
                    splittedLog.bytesSend = splitLog[9];
                }
                else {
                    splittedLog.request = Merge(splitLog[5],splitLog[6]);
                    splittedLog.statusCode = splitLog[7];
                    splittedLog.bytesSend = splitLog[8];
                }
                splittedLog.datetime = Merge(splitLog[3], splitLog[4]);
                long long unixTime = ToUnix(splittedLog.datetime);
                if (unixTime >= arg.fromTimeValue){
                    if (splittedLog.statusCode[0] == '5'){
                        if (arg.isStatsValue){
                            requestWithServerErrorStatus[splittedLog.request] ++;
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                        else{
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        if (arg.windowTimeValue != 0) {
            long long maxRequestSize = 0;
            std::vector <long long> requests;
            while (std::getline(LogsFile, buffer)) {
                std::vector <std::string> splitLog = Split(buffer, ' ');
                LogData splittedLog;
                splittedLog.ip = splitLog[0];
                splitLog[3] = splitLog[3].substr(1, splitLog[3].size());
                splitLog[4] = splitLog[4].substr(0, splitLog[4].size()-1);
                splitLog[5] = splitLog[5].substr(1, splitLog[5].size());
                if (splitLog[7] == "HTTP/1.0\"") {
                    splitLog[7] = splitLog[7].substr(0, splitLog[7].size()-1);
                    splittedLog.request  = Merge(splitLog[5], splitLog[6]);
                    splittedLog.request = Merge(splittedLog.request, splitLog[7]);
                    splittedLog.statusCode = splitLog[8];
                    splittedLog.bytesSend = splitLog[9];
                }
                else {
                    splittedLog.request = Merge(splitLog[5],splitLog[6]);
                    splittedLog.statusCode = splitLog[7];
                    splittedLog.bytesSend = splitLog[8];
                }
                splittedLog.datetime = Merge(splitLog[3], splitLog[4]);
                long long unixTime = ToUnix(splittedLog.datetime);
                if (unixTime >= arg.fromTimeValue && unixTime <= arg.toTimeValue){
                    requests.push_back(unixTime);
                    if (requests[requests.size() -1] - requests[0] > arg.windowTimeValue){
                        if (requests.size()-1 > maxRequestSize){
                            maxRequestSize = requests.size()-1;
                        }
                        requests.erase(requests.begin());
                    }
                    if (splittedLog.statusCode[0] == '5'){
                        if (arg.isStatsValue){
                            requestWithServerErrorStatus[splittedLog.request] ++;
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                        else{
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                    }
                }
            }
            if (requests[requests.size() -1] - requests[0] <= arg.windowTimeValue){
                if (requests.size() > maxRequestSize){
                    maxRequestSize = requests.size();
                }
                requests.erase(requests.begin());
            }
            std::cout << "Max Requests in " << arg.windowTimeValue << " seconds is " << maxRequestSize << "\n";
        }   
        else{
            while (std::getline(LogsFile, buffer)) {
                std::vector <std::string> splitLog = Split(buffer, ' ');
                LogData splittedLog;
                splittedLog.ip = splitLog[0];
                splitLog[3] = splitLog[3].substr(1, splitLog[3].size());
                splitLog[4] = splitLog[4].substr(0, splitLog[4].size()-1);
                splitLog[5] = splitLog[5].substr(1, splitLog[5].size());
                if (splitLog[7] == "HTTP/1.0\"") {
                    splitLog[7] = splitLog[7].substr(0, splitLog[7].size()-1);
                    splittedLog.request  = Merge(splitLog[5], splitLog[6]);
                    splittedLog.request = Merge(splittedLog.request, splitLog[7]);
                    splittedLog.statusCode = splitLog[8];
                    splittedLog.bytesSend = splitLog[9];
                }
                else {
                    splittedLog.request = Merge(splitLog[5],splitLog[6]);
                    splittedLog.statusCode = splitLog[7];
                    splittedLog.bytesSend = splitLog[8];
                }
                splittedLog.datetime = Merge(splitLog[3], splitLog[4]);
                long long unixTime = ToUnix(splittedLog.datetime);
                if (unixTime >= arg.fromTimeValue && unixTime <= arg.toTimeValue){
                    if (splittedLog.statusCode[0] == '5'){
                        if (arg.isStatsValue){
                            requestWithServerErrorStatus[splittedLog.request] ++;
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                        else{
                            if (arg.isPrintValue){
                                if (file.is_open()){
                                    file << buffer + "\n";
                                    std::cout << buffer << "\n";
                                }
                                else{
                                    std::cout << buffer << "\n";
                                }
                            }
                            else if (file.is_open()){
                                file << buffer + "\n";
                            }
                        }
                    }
                }
            }
        }
    }
    std::vector <std::pair<std::string, int>> vectorWithErrorRequests(requestWithServerErrorStatus.begin(), requestWithServerErrorStatus.end());
    std::sort(vectorWithErrorRequests.begin(), vectorWithErrorRequests.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b){return a.second > b.second;});
    if(arg.statsValue > vectorWithErrorRequests.size()) {
        arg.statsValue = vectorWithErrorRequests.size();
    }
    for(int i = 0; i < arg.statsValue; ++i) {
        std::cout << vectorWithErrorRequests[i].second << " " << vectorWithErrorRequests[i].first << "\n";
    }

}
