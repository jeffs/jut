/** @file jut/fun/sudoku/cell.hpp Sudoku cells hold digits, or are empty. */

#ifndef JUT_FUN_SUDOKU_CELL_INCLUDED
#define JUT_FUN_SUDOKU_CELL_INCLUDED

// C++ standard
#include <cassert>
#include <istream>
#include <ostream>
#include <string>

namespace jut { // Jeff's UTilitites
namespace fun { // FUN and games
namespace sudoku {

// Interface

/** Holds a values in the range [1, 9], or is empty. */
class cell {
    static constexpr std::uint8_t to_value(int);
    std::uint8_t _value;    // 0 if cell is empty
  public:
    static constexpr int max_val = 9;
    static constexpr bool is_valid(int);
    constexpr cell();
    constexpr explicit cell(int i);
    constexpr void assign(int);
    constexpr void clear();
    constexpr bool empty() const;
    constexpr int val() const;
};

/** Cells are equal if they hold the same value or are both empty. */
constexpr bool operator==(cell, cell);
constexpr bool operator!=(cell, cell);

/** Values are represented by '0' through '9', and empty cells by '.'. */
constexpr char to_char(cell);
std::istream& operator>>(std::istream&, cell&);
std::ostream& operator<<(std::ostream&, cell);
std::string to_string(cell);

// Implementation

constexpr cell::cell(): _value() { }

constexpr cell::cell(int const i): _value(to_value(i)) { }

constexpr void cell::assign(int const i) { _value = to_value(i); }

constexpr void cell::clear() { _value = 0; }

constexpr bool cell::empty() const { return _value == 0; }

constexpr int cell::val() const { return _value; }

constexpr std::uint8_t cell::to_value(int const i) {
    assert(is_valid(i));
    return static_cast<std::uint8_t>(i);
}

constexpr bool cell::is_valid(int const i) {
    return 1 <= i && i <= max_val;
}

constexpr bool operator==(cell const x, cell const y) {
    return x.val() == y.val();
}

constexpr bool operator!=(cell const x, cell const y) {
    return x.val() != y.val();
}

constexpr char to_char(cell const x) {
    return x.empty() ? '.' : static_cast<char>('0' + x.val());
}

}
}
}

#endif

