#include "jut/txt/date.hpp"

// Local
#include "jut/err/site.hpp"

// C++ standard
#include <ctime>

namespace jut {
namespace txt {

std::string date_stamp() {
    char buffer[sizeof("YYYY-MM-DD")];
    std::time_t const now = JUT_ERR_CHECK_POSIX(std::time(nullptr));
    std::strftime(buffer, sizeof buffer, "%F", localtime(&now));
    return buffer;
}

}
}
