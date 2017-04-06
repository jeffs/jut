/** @file jut/txt/split.hpp Expands strings into sequences of substrings. */

#ifndef JUT_TXT_SPLIT_INCLUDED
#define JUT_TXT_SPLIT_INCLUDED

// C++ standard
#include <string>
#include <vector>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

/** @return Whitespace-separated components of the specified string, as
 * determined by `operator>>(std::istringstream&, std::string&)`.
 */
std::vector<std::string> split(std::string const&);

/** @return Delimited components of the specified string. */
std::vector<std::string> split(std::string const&, char delimiter);

}
}

#endif

