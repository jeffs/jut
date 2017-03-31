#include "jut/txt/trim.hpp"

// C++ standard
#include <locale>

namespace jut {

std::string txt::trim(std::string const& s) {
    std::locale loc;
    auto b = begin(s), e = end(s);
    for (; b != e && std::isspace(*b, loc); ++b) { }
    for (; b != e && std::isspace(*(e - 1), loc); --e) { }
    return std::string(b, e);
}

std::string txt::trim_margin(std::string const& s, char c) {
    std::string r;
    for (auto p = begin(s), e = end(s); p != e;) {  // for each line
        while (p != e && *p != c) ++p;
        if (p != e) {
            auto i = ++p;
            while (p != e && *p != '\n') ++p;
            r.append(i, p == e ? p : ++p);
        }
    }
    return r;
}

}
