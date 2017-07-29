/** @file jut/fun/sudoku.hpp Supports programs related to the game Sudoku. */

#ifndef JUT_FUN_SUDOKU_INCLUDED
#define JUT_FUN_SUDOKU_INCLUDED

// C++ standard
#include <array>
#include <cassert>
#include <istream>
#include <ostream>
#include <string>

namespace jut { // Jeff's UTilitites
namespace fun { // FUN and games

namespace sudoku {

    class cell {

        using value_type = std::uint8_t;

        static constexpr value_type to_value(int const i) {
            assert(is_valid(i));
            return static_cast<value_type>(i);
        }

        static constexpr value_type to_value(char const c) {
            assert(is_valid(c));
            return c == '.' ? 0 : static_cast<value_type>(c - '0');
        }

        value_type _value;  // 0 for empty cell, 1-9 for corresponding digits

      public:

        static constexpr bool is_valid(int const i) {
            return 0 <= i && i <= 9;
        }

        static constexpr bool is_valid(char const c) {
            return c == '.' || ('0' <= c && c <= '9');
        }

        constexpr explicit cell(): _value() { }
        constexpr cell(int const i): _value(to_value(i)) { }
        constexpr cell(char const c): _value(to_value(c)) { }
        constexpr cell(cell const&) = default;

        constexpr bool empty() const { return _value == 0; }

        constexpr char to_char() const { return empty() ? '.' : _value + '0'; }

        cell& operator=(cell const&) = default;
        cell& operator=(char const c) { return *this = cell(c); }

        friend constexpr bool operator==(cell const a, cell const b) {
            return a._value == b._value;
        }

        friend constexpr bool operator!=(cell const a, cell const b) {
            return a._value != b._value;
        }

    };

    std::istream& operator>>(std::istream&, cell&);
    std::ostream& operator<<(std::ostream&, cell);

    std::string to_string(cell);

    constexpr std::size_t
        subgrid_height = 3, subgrid_width = 3,  // subgrids are 3 cells square
        board_height   = 9, board_width   = 9;  // boards are 3 subgrids square

    using row   = std::array<cell, board_width>;
    using board = std::array<row, board_height>;

    std::istream& operator>>(std::istream&, board&);
    std::ostream& operator<<(std::ostream&, board const&);

    std::string to_string(board const&);

    /** Populates all empty cells to complete the specified board, if possible.
     * Returns true on success, and false otherwise.  On success, each row,
     * each column, and each of the nine non-overlapping 3x3 sub-grids contains
     * all of the digits 1 through 9.  Note that this routine modifies the
     * board internally, but restores its initial state on failure.
     */
    bool solve(board&);
}

}
}

#endif

