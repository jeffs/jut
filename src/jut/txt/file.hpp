#ifndef JUT_TXT_FILE_INCLUDED
#define JUT_TXT_FILE_INCLUDED

// C++ Standard
#include <fstream>
#include <stdexcept>
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

template <class S>
std::ifstream open(S&& fname) {
    using namespace std::string_literals;
    std::ifstream file(std::forward<S>(fname));
    if (!file)
        throw std::runtime_error(fname + " is not a readable file"s);
    return file;
}

}
}

#endif
