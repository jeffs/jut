/** @file jut/txt/trim.hpp Removes specified characters from strings. */

#ifndef JUT_TXT_TRIM_INCLUDED
#define JUT_TXT_TRIM_INCLUDED

// C++ standard
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

/** Removes leading and trailing whitespace from the specified string. */
std::string trim(std::string const&);

/** Removes leading characters, up to a marker, from each line in a string.
 * Characters up to and including the first instance of the marker are removed
 * from each line.  If a line does not contain the marker, the entire line is
 * removed.
 */
std::string trim_margin(std::string const&, char marker ='|');

}
}

#endif

