/** @file jut/txt/trim.hpp Removes specified characters from strings. */

#ifndef JUT_TXT_TRIM_INCLUDED
#define JUT_TXT_TRIM_INCLUDED

// C++ standard
#include <string>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

std::string trim(std::string const& s);

std::string trim_margin(std::string const& s, char c ='|');

}
}

#endif

