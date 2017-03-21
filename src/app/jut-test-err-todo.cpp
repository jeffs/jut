/** @file app/jut-test-err-todo.cpp Test driver for jut/err/todo. */

#include "jut/err/todo.hpp"

// C++ standard
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#define TODO JUT_ERR_TODO

#define TEST(FUN) test(#FUN, [] { FUN; });

template <class F>
void test(std::string s, F f) try {
    f();
    throw s + " did not throw an exception";
} catch (jut::err::site_logic_error const& x) {
    std::cerr << x.what() << '\n';
    if (std::string(x.what()).find("TODO") == std::string::npos)
        throw s + " message does not contain TODO";
} catch (...) {
    throw s + " threw the wrong exception";
}

void f() { TODO }
struct s { s& operator++() { TODO } };

int main() try {
    TEST(([] { TODO })())
    TEST(f())
    TEST(++s{})
} catch (std::string const& what) {
    std::clog << "FAIL: " << what << '\n';
    return 1;
}
