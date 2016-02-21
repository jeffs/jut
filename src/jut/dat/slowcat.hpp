/** @file jut/dat/slowcat.hpp Slowly copies data from one stream to another.
 *
 * @todo Async.
 * @todo Unbuffer.
 */

#ifndef JUT_DAT_SLOWCAT_INCLUDED
#define JUT_DAT_SLOWCAT_INCLUDED

// C++ standard
#include <chrono>
#include <iosfwd>

namespace jut { // Jeff's UTilities
namespace dat { // DATa structures and manipulation

std::chrono::milliseconds const slowcat_delay_default(50);

/** Copies `input` to `output`, sleeping `period` before writing each byte. */
void slowcat(
        std::istream&             input,
        std::ostream&             output,
        std::chrono::milliseconds period =slowcat_delay_default);

/** Delegates to lvalue overload. */
inline void slowcat(
        std::istream&&            input,
        std::ostream&             output,
        std::chrono::milliseconds period =slowcat_delay_default) {
    slowcat(input, output, period);
}

}   // dat
}   // jut

#endif
