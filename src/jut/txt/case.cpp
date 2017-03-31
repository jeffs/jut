#include "jut/txt/case.hpp"

// C++ standard
#include <locale>

namespace jut {

std::string txt::to_lower(std::string s) {
    std::transform(begin(s), end(s), begin(s), [loc = std::locale()](char c) {
        return std::tolower(c, loc);
    });
    return s;
}

}
