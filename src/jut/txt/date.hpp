/** @file jut/txt/date.hpp Supports date formatting. */

#ifndef JUT_TXT_DATE_INCLUDED
#define JUT_TXT_DATE_INCLUDED

// C++ standard
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

/** Returns an ISO 8601 compliant representation of the specified date.  The
 * The date should be the C.E. year, 1-based month, and 1-based day of month;
 * e.g., `date_stamp(1929, 2, 14)` represnts the date of the Valentine's Day
 * Massacre.
 */
std::string date_stamp(int year, int month, int day);

/** Returns a stamp representing the current date. */
std::string date_stamp();

}
}

#endif

