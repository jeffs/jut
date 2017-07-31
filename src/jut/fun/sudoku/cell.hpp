/** @file jut/fun/sudoku/cell.hpp Sudoku cells hold digits, or are empty. */

#ifndef JUT_FUN_SUDOKU_CELL_INCLUDED
#define JUT_FUN_SUDOKU_CELL_INCLUDED

// C++ standard
#include <istream>
#include <ostream>
#include <string>

namespace jut { // Jeff's UTilitites
namespace fun { // FUN and games
namespace sudoku {

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

}
}
}

#include "jut/fun/sudoku/cell_imp.hpp"
#endif

