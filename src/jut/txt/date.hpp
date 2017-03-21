/** @file jut/txt/date.hpp Formats the current date as a YYYY-MM-DD string. */

#ifndef JUT_TXT_DATE_INCLUDED
#define JUT_TXT_DATE_INCLUDED

// C++ standard
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

/** Returns the current date as a string of the form YYYY-MM-DD.  The format
 * matches the output of `date +%F`; see `date(1)`.
 */
std::string date_stamp();

}
}

#endif

