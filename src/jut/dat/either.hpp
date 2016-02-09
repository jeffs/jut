/** @file jut/dat/either.hpp Algebraic type having two branches. */

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

template<class L, class R>  // Left, Right
class either {

    // PRIVATE FIELDS
    union { L _left; R _right; };
    bool _is_right;

    // PRIVATE METHODS
    either(false_type, L value): _left(std::move(value)), _is_right(false) { }
    either(true_type, R value): _right(std::move(value)), _is_right(true) { }

  public:

    // PUBLIC STATIC METHODS

    template<class L1, class =std::enable_if<std::is_same<L, L1>{}>>
    static either make_left(L1&& value) {
        return {false_type{}, std::forward<L1>(value)};
    }

    template<class R1, class =std::enable_if<std::is_same<R, R1>{}>>
    static either make_right(R1&& value) {
        return {true_type{}, std::forward<R1>(value)};
    }

    // PUBLIC METHODS

    // Special member functions

    template<class E, class =std::enable_if_t<std::is_same<E, either>{}>>
    either(E&& rhs):
        _is_right(rhs._is_right) {
        if (is_left()) new (&_left)  L(std::forward<E>(rhs)._left);
        else           new (&_right) R(std::forward<E>(rhs)._right);
    }

    template<class E, class =std::enable_if_t<std::is_same<E, either>{}>>
    either& operator=(E&& rhs) & {
        if (is_left()) {
            if (rhs.is_left()) {
                _left = std::forward<E>(rhs)._left;
            } else {
                _left.~L();
                new (&_right) R(std::forward<R>(rhs)._right);
            }
        } else if (rhs.is_left()) {
            _right.~R();
            new (&_left) L(std::forward<E>(rhs)._left);
        } else {
            _right = std::forward<E>(rhs)._right;
        }
        return *this;
    }

    ~either() { if (is_left()) _left.~L(); else _right.~R(); }

    // Manipulators

    L&& left() && { assert(is_left()); return std::move(_left); }
    R&& right() && { assert(is_right()); return std::move(_right); }

    L* leftp() { return is_left() ? &_left : nullptr; }
    R* rightp() { return is_right() ? &_right : nullptr; }

    // Accessors

    bool is_left() const { return !_is_right; }
    bool is_right() const { return _is_right; }

    L const& left() const& { assert(is_left()); return _left; }
    R const& right() const& { assert(is_right()); return _right; }

    L const* leftp() const { return is_left() ? &_left : nullptr; }
    R const* rightp() const { return is_right() ? &_right : nullptr; }

};

}   // dat
}   // jut

#endif
