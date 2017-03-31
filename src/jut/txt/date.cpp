#include "jut/txt/date.hpp"

// Local
#include "jut/err/site.hpp"

// C++ standard
#include <ctime>
#include <iomanip>
#include <sstream>

namespace jut {
namespace txt {

std::string date_stamp(int year, int month, int day) {
    JUT_ERR_CHECK(0 <= year);
    JUT_ERR_CHECK(year <= 9999);
    JUT_ERR_CHECK(1 <= month);
    JUT_ERR_CHECK(month <= 12);
    JUT_ERR_CHECK(1 <= day);
    JUT_ERR_CHECK(day <= 31);
    std::ostringstream out;
    out << std::setw(4) << std::setfill('0') << year << '-'
        << std::setw(2) << std::setfill('0') << month << '-'
        << std::setw(2) << std::setfill('0') << day;
    return out.str();
}

std::string date_stamp() {
    char buffer[sizeof("YYYY-MM-DD")];
    std::time_t const now = JUT_ERR_CHECK_POSIX(std::time(nullptr));
    std::strftime(buffer, sizeof buffer, "%F", localtime(&now));
    return buffer;
}

}
}
