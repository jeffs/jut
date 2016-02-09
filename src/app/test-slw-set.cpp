/** @file test-slw-set.cpp Test driver for jut/slw/set component. */

// Orchard
#include "jut/slw/set.hpp"

// C++ Standard
#include <cassert>
#include <iostream>
#include <string>

using namespace std::string_literals;

namespace slw = jut::slw;

using slw::operator+;
using slw::operator-;

using set = std::set<std::string>;

int main(int argc, char** argv) try {
    set bloomberg{"Brock", "Chris"};
    assert((bloomberg == set{"Brock", "Chris"}));
    assert((bloomberg - "Brock"s == set{"Chris"}));
    assert((bloomberg + "Alice"s == set{"Alice", "Brock", "Chris"}));
} catch (std::exception const& x) {
    std::clog << argv[0] << ": " << x.what() << std::endl;
}
