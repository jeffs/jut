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

std::vector<std::string> txt::split(std::string const& s, char d) {
    std::vector<std::string> result;
    if (!s.empty()) {
        std::string part;
        for (char c : s) {
            if (c == d) {
                result.push_back(move(part));
                part.clear();
            } else {
                part.push_back(c);
            }
        }
        result.push_back(move(part));
    }
    return result;
}

}
