#include "jut/err/site.hpp"

#include <ctime>
#include <iostream>

static std::string date_stamp() {
    char buffer[sizeof("YYYY-MM-DD")];
    std::time_t const now = JUT_ERR_CHECK_POSIX(std::time(nullptr));
    std::strftime(buffer, sizeof buffer, "%F", localtime(&now));
    return buffer;
}

int main(int argc, char** argv) {
    std::cout << date_stamp() << '\n';
}
