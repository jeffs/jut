#ifndef JUT_TXT_FILE_INCLUDED
#define JUT_TXT_FILE_INCLUDED

// C++ Standard
#include <fstream>
#include <string>
#include <vector>

namespace jut { // Jeff's UTilitites
namespace txt { // TeXT

struct open_error : std::runtime_error {
    using std::runtime_error::runtime_error;
};

std::fstream open(
        std::string const&      fname,
        std::ios_base::openmode mode =std::ios_base::in);

std::string slurp(std::string const& fname);

std::vector<std::string> slurp_lines(std::string const& fname);

}
}

#endif
