/** @file app/jut-test-txt-case.cpp Test driver for jut/txt/case. */

#include "jut/txt/case.hpp"

// C++ standard
#include <cassert>

int main() {
    assert(jut::txt::to_lower("") == "");
    assert(jut::txt::to_lower("Hello 42!") == "hello 42!");
}
