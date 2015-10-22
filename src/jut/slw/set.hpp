#ifndef JUT_SLW_SET_INCLUDED
#define JUT_SLW_SET_INCLUDED

// C++ Standard
#include <iostream>
#include <set>

namespace jut { // Jeff's UTilitites
namespace slw { // Standard Library Wrappers

template <class T>
std::set<T>& operator+=(std::set<T>& xs, T const& x) {
    xs.insert(x);
    return xs;
}

template <class T>
std::set<T>& operator-=(std::set<T>& xs, T const& x) {
    xs.erase(x);
    return xs;
}

template <class T>
std::set<T> operator+(std::set<T> xs, T const& x) {
    return xs += x;
}

template <class T>
std::set<T> operator-(std::set<T> xs, T const& x) {
    return xs -= x;
}

// TODO Generalize to accomodate all standard collections.
// TODO Omit final comma.
template <class T>
std::ostream& operator<<(std::ostream& out, std::set<T> const& xs) {
    out << "{ ";
    for (T const& x : xs)
        out << x << ", ";
    return out << "}";
}

}
}

#endif
