#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#pragma once
#ifndef STRING_TOOLS_H
#define STRING_TOOLS_H

void WriteStringToFile(char const* filename, std::string output) {
    std::cout << output << std::endl;
    std::ofstream fout(filename, std::ios::out);
    if (fout.is_open()) {
        fout << output;
        fout.close();
    }
}

std::string ReadStringFromFile(char const* filename) {
    std::ifstream fin(filename, std::ios::in);
    std::string str((std::istreambuf_iterator<char>(fin)), (std::istreambuf_iterator<char>()));
    std::cout << str << std::endl;
    return str;
}

std::vector<char> StringToCharVector(std::string input) {
    std::vector<char> res;
    std::copy(input.begin(), input.end(), std::back_inserter(res));
    return res;
}

std::string CharVectorToString(std::vector<char> input) {
    std::string res = std::string (input.begin(), input.end());
    return res;
}

#endif
