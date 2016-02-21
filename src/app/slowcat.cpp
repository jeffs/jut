/** @file app/slowcat.cpp Slowly writes data from standard input.  Useful for
 * sending data to command-line programs at a rate typical of a human being
 * typing manually.
 *
 * @todo Accept period as command-line flag.
 *
 * @todo Interact directly with terminal, to make sure `unbuffer` wrapping is
 * unnecessary.
 */

// Local
#include "jut/dat/slowcat.hpp"

// C++ standard
#include <exception>
#include <iostream>

namespace dat = jut::dat;

int main(int argc, char** argv) try {
    if (argc > 1) {
        std::clog << "Usage: slowcat\n(arguments are not supported)";
        return 1;
    }
    dat::slowcat(std::cin, std::cout);
} catch (std::exception const& x) {
    std::clog << "slowcat: " << x.what() << std::endl;
}
