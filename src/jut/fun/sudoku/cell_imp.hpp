// C++ standard
#include <cassert>

namespace jut { // Jeff's UTilitites
namespace fun { // FUN and games

namespace sudoku {

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

}   // namespace sudoku

constexpr bool sudoku::operator==(cell const x, cell const y) {
    return x.val() == y.val();
}

constexpr bool sudoku::operator!=(cell const x, cell const y) {
    return x.val() != y.val();
}

constexpr char sudoku::to_char(cell const x) {
    return x.empty() ? '.' : static_cast<char>('0' + x.val());
}

}
}

