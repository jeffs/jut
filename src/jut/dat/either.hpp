/** @file jut/dat/either.hpp Generic variant type having two branches.
 *
 * @todo allocator awareness
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

template <class T> struct left_t { T value; };
template <class T> struct right_t { T value; };

/** Holds either an `L` or an `R` at any given time. */
template <class L, class R>  // Left, Right
class either {

    // PRIVATE NON-STATIC DATA MEMBERS
    union { L _left; R _right; };
    bool _is_right;

    // PRIVATE NON-STATIC MEMBER FUNCTIONS
    either(false_type, L value): _left(std::move(value)), _is_right(false) { }
    either(true_type, R value): _right(std::move(value)), _is_right(true) { }

  public:

    // PUBLIC STATIC MEMBER FUNCTIONS

    static
    either make_left(L value) { return {false_type{}, std::move(value)}; }

    static
    either make_right(R value) { return {true_type{}, std::move(value)}; }

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

    L&& left() && { assert(is_left()); return std::move(_left); }
    R&& right() && { assert(is_right()); return std::move(_right); }

    L* leftp() { return is_left() ? &_left : nullptr; }
    R* rightp() { return is_right() ? &_right : nullptr; }

    // const

    bool is_left() const { return !_is_right; }
    bool is_right() const { return _is_right; }

    L const& left() const& { assert(is_left()); return _left; }
    R const& right() const& { assert(is_right()); return _right; }

    L const* leftp() const { return is_left() ? &_left : nullptr; }
    R const* rightp() const { return is_right() ? &_right : nullptr; }

};

template <class T>
left_t<T> make_left(T&& value) { return {std::forward<T>(value)}; }

template <class T>
right_t<T> make_right(T&& value) { return {std::forward<T>(value)}; }

}   // dat
}   // jut

#endif
