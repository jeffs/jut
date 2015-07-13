// Orchard
#include "jut/txt/file.hpp"
#include "jut/txt/roll.hpp"

// C++ Standard
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace txt = jut::txt;

int main(int argc, char** argv) try {
    if (argc < 2) {
        txt::roll(std::cin, std::cout);
    } else {
        while (*++argv)
            txt::roll(txt::open(*argv), std::cout);
    }
} catch (std::exception const& x) {
    std::clog << "roll: " << x.what() << std::endl;
}
