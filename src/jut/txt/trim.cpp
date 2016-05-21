#include "jut/txt/trim.hpp"

// C++ standard

namespace jut {

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
