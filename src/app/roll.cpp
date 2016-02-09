/** @file app/roll.cpp Prints text from files or standard input.
 *
 * @todo Accept roll period, in millseconds, as command-line flag.
 */

// Local
#include "jut/txt/file.hpp"
#include "jut/txt/roll.hpp"

// C++ standard
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace txt = jut::txt;

/** Rolls out text from files named in `argv`, or text fromstandard input if
 * `argc` is less than two.
 */
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
