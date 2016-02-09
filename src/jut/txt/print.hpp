/** @file jut/txt/print.hpp Prints expressions and their values.
 *
 * The `print` templates print their arguments to a specified output stream, or
 * to the standard output stream if no other stream is specified.  Printed
 * values are separated by spaces, and followed by a newline character.
 */

#ifndef JUT_TXT_PRINT_INCLUDED
#define JUT_TXT_PRINT_INCLUDED

// C++ standard
#include <exception>
#include <iostream>
#include <type_traits>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

inline
std::ostream& print(std::ostream& out) {
    return out << '\n';
}

template <class T>
std::ostream& print(std::ostream& out, T const& x) {
    return out << x << '\n';
}

template <class T, class ...Ts>
std::ostream& print(std::ostream& out, T const& x, Ts const& ...xs) {
    return print(out << x << ' ', xs...);
}

template <class T, class ...Ts,
        class =std::enable_if_t<!std::is_base_of<std::ostream, T>{}>>
std::ostream& print(T const& x, Ts const& ...xs) {
    return print(std::cout, x, xs...);
}

}
}

#endif
