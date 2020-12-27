#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <filesystem>
#include <direct.h>
#include "compressor.h"
#include "string_tools.h"
#include "binary_tools.h"
#include <regex>

std::regex regex_file("[\\w]+\\.[\\w]+$", std::regex::ECMAScript);
std::regex regex_file_extension("\\.[\\w]+$", std::regex::ECMAScript);

int main(int argc, char *argv[]) {
    if (argc == 3) {
        std::filesystem::path cwd = std::filesystem::current_path();
        if (strcmp(argv[2], "code_to") == 0 || strcmp(argv[2], "codeto") == 0 || strcmp(argv[2], "code") == 0 || strcmp(argv[2], "c") == 0) {
            try {
                std::string inputfilename(argv[1]);
                std::smatch mr;

                if (std::regex_search(inputfilename, mr, regex_file_extension)) {
                    std::string filetype (mr[0]);
                    inputfilename = std::regex_replace(argv[1], regex_file_extension, ".gau");
                    inputfilename = cwd.string() + "\\" + inputfilename;
                    WriteAllBytes(inputfilename.c_str(),
                                  StringToCharVector(Code(filetype + "\n" + CharVectorToString(ReadAllBytes(argv[1])))));
                } else {
                    cout << "Enter file name with file extension!";
                }

            } catch (...) {
                std::cout << "Exception!" << std::endl;
            }
        } else if (strcmp(argv[2], "decode_to") == 0 || strcmp(argv[2], "decodeto") == 0 || strcmp(argv[2], "decode") == 0 || strcmp(argv[2], "d") == 0) {
            try {
                std::string outputfilename(argv[1]);
                std::smatch mr;
                if (std::regex_search(outputfilename, mr, regex_file_extension)) {
                    std::string filetype (mr[0]);
                    if (filetype != ".gau") {
                        cout << "Wrong file extension, it should be .gau!";
                    }
                }
                if (std::regex_match(argv[1], regex_file)) {
                    outputfilename = std::regex_replace(argv[1], regex_file_extension, "");
                }
                string decoded = Decode(CharVectorToString(ReadAllBytes(argv[1])));
                string filetype (decoded.begin(), std::find(decoded.begin(), decoded.end(), '\n'));
                string fileload (std::find(decoded.begin(), decoded.end(), '\n') + 1, decoded.end());
                WriteAllBytes((cwd.string() + "\\" + outputfilename + filetype).c_str(), StringToCharVector(fileload));
            } catch (...) {
                std::cout << "Exception!" << std::endl;
            }
        } else {
            cout << "Wrong arguments!";
        }
    } else if (argc == 2) {
        if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "Help") == 0) {
            std::cout << "To code file enter '[name of file you want to code with extension] code [name of result file without extension]'\n"
                         "To decode file enter '[name of file you want to decode] decode [name of result file with extension]'\n" << std::endl;
        }
    } else {
        std::cout << "\nWrong amount of arguments! Type pass 'help' argument to see help menu." << std::endl;
    }

    return EXIT_SUCCESS;
}