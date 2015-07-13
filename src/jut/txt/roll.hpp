#ifndef JUT_TXT_ROLL_INCLUDED
#define JUT_TXT_ROLL_INCLUDED

// C++ Standard
#include <chrono>
#include <iosfwd>
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

const std::chrono::milliseconds roll_period_default(3);

void roll(
        std::string const& line,
        std::ostream&,
        std::chrono::milliseconds =roll_period_default);

void roll(
        std::istream& lines,
        std::ostream&,
        std::chrono::milliseconds =roll_period_default);

}
}

#endif
