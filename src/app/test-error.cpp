/** @file app/test-error.cpp Test driver for component jut/err/error. */

#include "jut/err/error.hpp"

// Local
#include "jut/txt/print.hpp"

// C++ standard
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using namespace std::literals;

using jut::err::site_logic_error;

#define FAIL0 std::clog << __FILE__ << ':' << __LINE__ << ": FAIL\n";

#define FAIL1(X) jut::txt::print( \
        std::clog << __FILE__ << ':' << __LINE__ << ": FAIL: ", (X));

int main() try {

    // operator<<

    std::ostringstream out;
    out << site_logic_error("Here I am.", "some/file.cpp", 42);
    if (out.str() != "some/file.cpp:42: Here I am.") FAIL1(out.str());

    // JUT_ERR_THROW_LOGIC

    try { JUT_ERR_THROW_LOGIC("hello") }
    catch (site_logic_error const& x) {
        auto const line = __LINE__ - 2;
        if (x.file != __FILE__ || x.line != line || x.what() != "hello"s)
            FAIL1(x)
    }

    // JUT_ERR_ASSERT

    try { JUT_ERR_ASSERT(0 == 0) }
    catch (site_logic_error const& x) { FAIL1(x) }

    try { JUT_ERR_ASSERT(0 != 0) FAIL0 }
    catch (site_logic_error const&) { }

    // JUT_ERR_ASSERT_EQ

    try { JUT_ERR_ASSERT_EQ(0, 0) }
    catch (site_logic_error const& x) { FAIL1(x) }

    try { JUT_ERR_ASSERT_EQ(0, 1) FAIL0 }
    catch (site_logic_error const&) { }

} catch (site_logic_error const& x) {
    std::cerr << "Error: " << x << '\n';
} catch (std::exception const& x) {
    std::cerr << "Error: " << x.what() << '\n';
}
