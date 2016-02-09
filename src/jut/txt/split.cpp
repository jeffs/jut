#include "jut/txt/split.hpp"

// C++ standard
#include <sstream>

namespace jut {

std::vector<std::string> txt::split(std::string const& s) {
    std::vector<std::string> result;
    std::istringstream in(s);
    for (std::string word; in >> word;)
        result.push_back(word);
    return result;
}

}
