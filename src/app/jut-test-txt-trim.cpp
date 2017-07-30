/** @file app/jut-test-txt-trim.cpp Test driver for component jut/txt/trim. */

// Local
#include "jut/txt/trim.hpp"

// C++ standard
#include <cassert>

int main() {
    assert("" == jut::txt::trim_margin(""));
    assert("" == jut::txt::trim_margin("  |"));
    assert("hello" == jut::txt::trim_margin("|hello"));
    assert("hello" == jut::txt::trim_margin(" |hello"));
    assert("hello" == jut::txt::trim_margin("  |hello"));

    assert("{ \"hello\": 1,\n  \"world\": 2 }\n" ==
            jut::txt::trim_margin(R"(|{ "hello": 1,
                                     |  "world": 2 }
                                     |)"));

    assert("{ \"hello\": 1,\n  \"world\": 2 }\n\n" ==
            jut::txt::trim_margin(R"(|{ "hello": 1,
                                     |  "world": 2 }
                                     |
                                  )"));
}
