#include "jut/txt/roll.hpp"

#include <fstream>
#include <iostream>

namespace txt = jut::txt;

int main(int argc, char** argv) {
    if (argc < 2) {
        txt::roll(std::cin, std::cout);
    } else {
        for (auto fname = argv; *++fname;) {
            std::ifstream file(*fname);
            if (!file) {
                std::cerr << *fname << ": not a readable file\n";
                return 1;
            }
            txt::roll(file, std::cout);
        }
    }
}
