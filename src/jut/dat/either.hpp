/** @file jut/dat/either.hpp Generic variant type having two branches.
 *
 * @todo allocator awareness
 * @todo `emplace_left`, `emplace_right`
 * @todo specialize `std::hash`
 * @todo ordered comparisons (`<` et al)
 */

#ifndef JUT_DAT_EITHER_INCLUDED
#define JUT_DAT_EITHER_INCLUDED

// C++ standard
#include <cassert>
#include <type_traits>
#include <utility>

namespace jut { // Jeff's UTilities
namespace dat { // DATa structures

using std::false_type;
using std::true_type;

namespace detail {

/** C++17 will provide `std::invoke`. */
template <class F, class ...Ts>
constexpr decltype(auto) invoke(F&& f, Ts&&... xs) {
    return std::forward<F>(f)(std::forward<Ts>(xs)...);
}

template <class F, class Ts, std::size_t ...Is>
constexpr decltype(auto) apply_imp(
        F&&  f,
        Ts&& xs,
        std::index_sequence<Is...>) {
    return invoke(std::forward<F>(f), std::get<Is>(std::forward<Ts>(xs))...);
}

/** @note C++17 may provide `std::apply`. */
template <class F, class T>
constexpr decltype(auto) apply(F&& f, T&& xs) {
    return apply_imp(
            std::forward<F>(f),
            std::forward<T>(xs),
            std::make_index_sequence<std::tuple_size<std::decay_t<T>>{}>{});
}

}   // detail

template <class ...Ts>
struct left_branch {
    std::tuple<Ts...> arguments;
    explicit left_branch(Ts&&... xs): arguments(xs...) { }
};

template <class ...Ts>
left_branch<Ts...> make_left(Ts&&... args) {
    return left_branch<Ts...>{std::forward<Ts>(args)...};
}

template <class ...Ts>
struct right_branch {
    std::tuple<Ts...> arguments;
    explicit right_branch(Ts&&... xs): arguments(xs...) { }
};

template <class ...Ts>
right_branch<Ts...> make_right(Ts&&... args) {
    return right_branch<Ts...>{std::forward<Ts>(args)...};
}

/** Holds either an `L` or an `R` at any given time. */
template <class L, class R>  // Left, Right
class either {

    // PRIVATE NON-STATIC DATA MEMBERS

    union { L _left; R _right; };
    bool _is_right;

    // PRIVATE NON-STATIC MEMBER FUNCTIONS

    template <class T>
    either(false_type, T&& value):
        _left(std::forward<T>(value)), _is_right(false) { }

    template <class T>
    either(true_type, T&& value):
        _right(std::forward<T>(value)), _is_right(true) { }

    either(true_type, R&& value): _right(std::move(value)), _is_right(true) { }

  public:

    // PUBLIC STATIC MEMBER FUNCTIONS

    template <class T>
    static either make_left(T&& value) {
        return {false_type{}, std::forward<T>(value)};
    }

    template <class T>
    static either make_right(T&& value) {
        return {true_type{}, std::forward<T>(value)};
    }

    // PUBLIC METHODS

    // Special member functions, ordered as in [special]: default constructor,
    // copy constructor and copy assignment operator, move constructor and move
    // assignment operator, and destructor.

    either(): _left(), _is_right(false) { }

    either(either const& rhs):
        _is_right(rhs._is_right) {
        if (is_left()) new (&_left)  L(rhs._left);
        else           new (&_right) R(rhs._right);
    }

    either& operator=(either const& rhs) & {
        if (is_left()) {
            if (rhs.is_left()) {
                _left = rhs._left;
            } else {
                _left.~L();
                new (&_right) R(rhs._right);
            }
        } else if (rhs.is_left()) {
            _right.~R();
            new (&_left) L(rhs._left);
        } else {
            _right = rhs._right;
        }
        _is_right = rhs._is_right;
        return *this;
    }

    either(either&& rhs):
        _is_right(rhs._is_right) {
        if (is_left()) new (&_left)  L(std::move(rhs._left));
        else           new (&_right) R(std::move(rhs._right));
    }

    either& operator=(either&& rhs) & {
        if (is_left()) {
            if (rhs.is_left()) {
                _left = std::move(rhs._left);
            } else {
                _left.~L();
                new (&_right) R(std::move(rhs._right));
            }
        } else if (rhs.is_left()) {
            _right.~R();
            new (&_left) L(std::move(rhs._left));
        } else {
            _right = std::move(rhs._right);
        }
        _is_right = rhs._is_right;
        return *this;
    }

    ~either() {
        if (is_left()) _left.~L();
        else           _right.~R();
    }

    // non-const

    template <class T>
    either(left_branch<T> const& branch):
        _is_right(false) {
        new (&_left) L(branch.value);
    }

    template <class... Ts>
    either(left_branch<Ts...>&& branch):
        _is_right(false) {
        detail::apply(
            [this](auto&&... xs) {
                new (&_left) L(std::forward<decltype(xs)>(xs)...);
            },
            std::move(branch.arguments));
    }

    template <class T>
    either(right_branch<T> const& branch):
        _is_right(true) {
        new (&_right) R(branch.value);
    }

    template <class... Ts>
    either(right_branch<Ts...>&& branch):
        _is_right(true) {
        detail::apply(
            [this](auto&&... xs) {
                new (&_right) R(std::forward<decltype(xs)>(xs)...);
            },
            std::move(branch.arguments));
    }

    template <class ...Ts>
    void emplace_left(Ts&&... xs) {
        this->~either();
        _is_right = false;
        new (&_left) L(std::forward<Ts>(xs)...);
    }

    template <class ...Ts>
    void emplace_right(Ts&&... xs) {
        this->~either();
        _is_right = true;
        new (&_right) R(std::forward<Ts>(xs)...);
    }

    L& left()  & { assert(is_left());  return _left;  }
    R& right() & { assert(is_right()); return _right; }

    L&& left()  && { assert(is_left());  return std::move(_left);  }
    R&& right() && { assert(is_right()); return std::move(_right); }

    L* leftp()  { return is_left()  ? &_left  : nullptr; }
    R* rightp() { return is_right() ? &_right : nullptr; }

    // const

    bool is_left()  const { return !_is_right; }
    bool is_right() const { return  _is_right; }

    L const& left()  const& { assert(is_left());  return _left;  }
    R const& right() const& { assert(is_right()); return _right; }

    L const* leftp()  const { return is_left()  ? &_left  : nullptr; }
    R const* rightp() const { return is_right() ? &_right : nullptr; }

};

template <class L, class R>
bool operator==(either<L, R> const& lhs, either<L, R> const& rhs) {
    return (lhs.is_left()  && rhs.is_left()  && lhs.left()  == rhs.left())
        || (lhs.is_right() && rhs.is_right() && lhs.right() == rhs.right());
}

template <class L, class R>
bool operator!=(either<L, R> const& lhs, either<L, R> const& rhs) {
    return !(lhs == rhs);
}

}   // dat
}   // jut

#endif
