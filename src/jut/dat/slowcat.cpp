#include "jut/dat/slowcat.hpp"

// C++ standard
#include <iostream>
#include <thread>

namespace jut {

void dat::slowcat(
        std::istream&             input,
        std::ostream&             output,
        std::chrono::milliseconds period) {
    for (char c; input.get(c);) {
        std::this_thread::sleep_for(period);
        output.put(c);
    }
}

}
