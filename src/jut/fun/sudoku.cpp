#include "jut/fun/sudoku.hpp"

// C++ standard

// XXX
#include <iostream>

namespace {

using jut::fun::sudoku::board;
using jut::fun::sudoku::cell;

}

namespace jut {
namespace fun {

std::istream& sudoku::operator>>(std::istream& in, cell& out) {
    char c;
    if (in >> c) {
        if (cell::is_valid(c))
            out = cell(c);
        else
            in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::ostream& sudoku::operator<<(std::ostream& out, cell const in) {
    return out << in.to_char();
}

std::string to_string(cell const c) {
    return std::string(1, c.to_char());
}

std::istream& sudoku::operator>>(std::istream& in, board& out) {
    board r;
    for (row& xs : r)
        for (cell& x : xs)
            if (!(in >> x))
                return in;
    out = r;
    return in;
}

std::ostream& sudoku::operator<<(std::ostream& out, board const& in) {
    return out << to_string(in);
}

// Inserts two blank columns between horizontally adjacent subgrids, and a
// blank line between vertically adjacent subgrids.
std::string sudoku::to_string(board const& in) {
    std::string r;
    for (std::size_t i = 0; i < board_height; ++i) {
        if (i != 0 && i % subgrid_height == 0)
            r.push_back('\n');
        for (std::size_t j = 0; j < board_width; ++j) {
            if (j != 0 && j % subgrid_width == 0)
                r += "  ";
            r.push_back(in[i][j].to_char());
        }
        r.push_back('\n');
    }
    return r;
}

bool sudoku::solve(board&) {
    return false; // TODO
}

}
}
