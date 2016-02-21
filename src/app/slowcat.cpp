/** @file app/slowcat.cpp Slowly writes data from named files or standard
 * input.  Useful for sending data to command-line programs at a rate typical
 * of a human being typing manually.
 *
 * @todo Accept period as command-line flag.
 */

// Local
#include "jut/txt/file.hpp"
#include "jut/dat/slowcat.hpp"

// C++ standard
#include <exception>
#include <ios>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace dat = jut::dat;
namespace txt = jut::txt;

int main(int argc, char** argv) try {
    if (argc < 2) {
        dat::slowcat(std::cin, std::cout);
    } else {
        while (*++argv)
            dat::slowcat(txt::open(*argv, std::ios::binary), std::cout);
    }
} catch (std::exception const& x) {
    std::clog << "slowcat: " << x.what() << std::endl;
}
