#include "jut/err/site.hpp"
#include "jut/txt/trim.hpp"

#include <ctime>
#include <fstream>
#include <iostream>

static std::string date_stamp() {
    char buffer[sizeof("YYYY-MM-DD")];
    std::time_t const now = JUT_ERR_CHECK_POSIX(std::time(nullptr));
    std::strftime(buffer, sizeof buffer, "%F", localtime(&now));
    return buffer;
}

static std::string strip_comment(std::string const& line) {
    auto e = line.find('#');
    return e == std::string::npos ? line : line.substr(0, e);
}

static bool get_line(std::istream& in, std::string& line) {
    while (std::getline(in, line)) {
        line = jut::txt::trim(strip_comment(line));
        if (!line.empty())
            return true;
    }
    return false;
}

int main(int argc, char** argv) try {
    std::string const path = "/Users/jeff/home/fit/log/" + date_stamp();
    std::ifstream in(path);
    if (!in)
        throw "can't read file: " + path;
    for (std::string line; get_line(in, line);)
        std::cout << line << '\n';
} catch (char const* what) {
    std::clog << "error: " << what << '\n';
    return 1;
} catch (std::string const& what) {
    std::clog << "error: " << what << '\n';
    return 1;
} catch (std::runtime_error const& error) {
    std::clog << "error: " << error.what() << '\n';
    return 2;
}
