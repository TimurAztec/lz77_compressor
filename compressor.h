#include <iostream>
#include <string>
#include <tuple>
#include <bitset>
#include <sstream>
#include <fstream>
#include "loading.h"

using namespace std;

/**
Given two strings s1 and s2, find the longest prefix of s2 that is in s1
and returns the position of the prefix' first character in s1 and its length in a pair

If s1 = "lossless compression in opposition to " and s2 = "lossy compression", the longest prefix is "loss"
and the function returns (0, 4).
*/
pair<int, int> longest_prefix(string s1, string s2)
{
    int pos {0};
    int length {0};

    for(int i = 0; i < s1.size(); i++)
    {
        int l {0};
        while(i+l < s1.size() && l < s2.size() && s1[i+l] == s2[l])
            l++;

        if(l > length)
        {
            pos = i;
            length = l;
        }

        if(i == s1.size() - length || length == s2.size())
            return pair<int,int>(pos, length);
    }

    return pair<int,int>(pos, length);
}

/**
we have a sliding window of fixed size and instead of rewriting text that already is in the window,
we just refer to it with its position in the window and its size
*/
string Code(string s)
{
    Loader loader;
    string compressed { "" };
    int window_size { 4095 };
    int pattern_size { 15 };
    int i { 0 };

    while(i < s.size())
    {
        string s1 { i >= window_size ? s.substr(i - window_size, window_size) : s.substr(0, i) };
        string s2 { s.substr(i, min(pattern_size, (int)s.size() - i)) };
        pair<int,int> match = longest_prefix(s1, s2); // fst = pos; snd = length

        loader.load((static_cast<float>(i) / s.size()) * 100, i, "Coding");
        if(match.second == 0) // length = 0: no match, we just add a char (0, char)
        {
            compressed += (char)0;
            compressed += s[i];

            i++;
        }
        else // match, then we add (pos, length)
        {
            int pos    = match.first;
            int length = match.second;
            compressed += (char) ((length << 4) | (pos >> 8));
            compressed += (char) (pos & 0xff);

            i += length;
        }
    }

    return compressed;
}

string Decode(string compressed)
{
    Loader loader;
    string s { "" };
    int window_size { 4095 };

    for(int i = 0; i < compressed.size(); i += 2)
    {
        loader.load((static_cast<float>(i) / compressed.size()) * 100, i, "Decoding");
        unsigned char byte1 = compressed[i];
        unsigned char byte2 = compressed[i+1];
        int length = ((int)byte1/16);

        if(length == 0)
        {
            s += byte2;
        }
        else
        {
            int pos = ((byte1 & 0xf) << 8) | byte2;

            s += s.substr(max(0, (int) s.size() - window_size) + pos, length);
        }
    }

    return s;
}