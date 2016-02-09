/** @file split.hpp Expands strings into sequences of substrings. */

#ifndef JUT_TXT_SPLIT_INCLUDED
#define JUT_TXT_SPLIT_INCLUDED

// C++ Standard
#include <string>
#include <vector>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

/** @return Whitespace-separated compoents of the specified string, as
 * determined by `operator>>(std::istringstream&, std::string&)`.
 */
std::vector<std::string> split(std::string const&);

}
}

#endif

