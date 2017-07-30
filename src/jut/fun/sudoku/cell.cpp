#include "jut/fun/sudoku/cell.hpp"

namespace jut {
namespace fun {

std::istream& sudoku::operator>>(std::istream& in, cell& r) {
    if (char c; in >> c) {
        if (c == '.')                   r.clear();
        else if ('0' < c && c <= '9')   r.assign(c - '0');
        else                            in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::ostream& sudoku::operator<<(std::ostream& out, cell const x) {
    return out << (x.empty() ? '.' : static_cast<char>('0' + x.val()));
}

std::string sudoku::to_string(cell const x) {
    return { to_char(x) };
}

}
}
