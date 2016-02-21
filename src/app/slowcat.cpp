/** @file app/slowcat.cpp Slowly writes data from standard input.
 *
 * The intent of this program is to sending data to command-line programs at a
 * rate typical of a human being typing manually.  In practice, `unbuffer -p`
 * and/or `nc -i 1` are more effective.
 *
 * @todo Accept period as command-line flag.
 * @todo Check `isatty` and disable any buffering.
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
