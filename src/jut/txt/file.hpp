#ifndef JUT_TXT_FILE_INCLUDED
#define JUT_TXT_FILE_INCLUDED

// C++ Standard
#include <fstream>
#include <string>
#include <vector>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

std::ifstream open(std::string const& fname);

std::string slurp(std::string const& fname);

std::vector<std::string> slurp_lines(std::string const& fname);

}
}

#endif
