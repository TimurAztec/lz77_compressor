#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#pragma once
#ifndef BINARYTOOLS_H
#define BINARYTOOLS_H

std::vector<char> ReadAllBytes(char const* filename)
{
    std::ifstream ifs(filename, std::ios::binary|std::ios::ate);
    std::ifstream::pos_type pos = ifs.tellg();

    std::vector<char>  result(pos);

    ifs.seekg(0, std::ios::beg);
    ifs.read(&result[0], pos);

    return result;
}

void WriteAllBytes(char const* filename,std::vector<char> data)
{
    std::ofstream fout;
    size_t size = data.size();
    fout.open(filename, std::ios::out | std::ios::binary);
    fout.write((char*)&data[0],size * sizeof(data[0]));
    fout.close();
}

#endif