/** @file app/jut-test-slw-set.cpp Test driver for component jut/slw/set. */

// Local
#include "jut/slw/set.hpp"

// C++ standard
#include <cassert>
#include <iostream>
#include <string>

using namespace std::string_literals;

namespace slw = jut::slw;

using slw::operator+;
using slw::operator-;

using set = std::set<std::string>;

int main(int, char** argv) try {
    set bloomberg{"Brock", "Chris"};
    assert((bloomberg == set{"Brock", "Chris"}));
    assert((bloomberg - "Brock"s == set{"Chris"}));
    assert((bloomberg + "Alice"s == set{"Alice", "Brock", "Chris"}));
} catch (std::exception const& x) {
    std::clog << argv[0] << ": " << x.what() << std::endl;
    return 1;
}
