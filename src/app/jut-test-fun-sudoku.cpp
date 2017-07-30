/** @file app/jut-test-fun-sudoku.cpp Test of jut/fun/sudoku sub-package. */

// Local
#include "jut/err/site.hpp"
#include "jut/fun/sudoku.hpp"
#include "jut/txt/trim.hpp"

// C++ standard
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

int main() try {

#if 0
    using board_t = jut::fun::sudoku::board;

    std::string const input = jut::txt::trim_margin(R"(
        |..8  .32  7.4
        |.7.  ...  ..2
        |5..  ...  ...
        |
        |...  ..1  6.7
        |..1  .8.  2..
        |7.4  3..  ...
        |
        |...  ...  ..1
        |2..  ...  .3.
        |8.3  51.  4..
    )");

    std::istringstream in(input);

    board_t board;
    assert(in >> board);

    JUT_ERR_ASSERT_EQ(board, (board_t{{
        {{ 0, 0, 8, 0, 3, 2, 7, 0, 4 }},
        {{ 0, 7, 0, 0, 0, 0, 0, 0, 2 }},
        {{ 5, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 1, 6, 0, 7 }},
        {{ 0, 0, 1, 0, 8, 0, 2, 0, 0 }},
        {{ 7, 0, 4, 3, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 1 }},
        {{ 2, 0, 0, 0, 0, 0, 0, 3, 0 }},
        {{ 8, 0, 3, 5, 1, 0, 4, 0, 0 }},
    }}));

    JUT_ERR_ASSERT_EQ(to_string(board), input);

#endif

} catch (jut::err::site_error const& err) {
    std::cerr << "FAIL: " << err.what() << '\n';
    return 1;
}
