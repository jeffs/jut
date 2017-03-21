/** @file app/nutrition.cpp Utility for daily diet tracking.
 *
 * @todo Load and store ingredients and recipes.
 * @todo Load and store daily diet logs.
 * @todo Sum and report macronutrients.
 */

#include "jut/err/site.hpp"
#include "jut/txt/case.hpp"
#include "jut/txt/date.hpp"
#include "jut/txt/trim.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

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
    std::string const path = "/Users/jeff/home/fit/log/" +
        jut::txt::date_stamp();
    std::ifstream in(path);
    if (!in)
        throw "can't read file: " + path;
    for (std::string line; get_line(in, line);) {
        double count;
        std::string unit, name;
        std::istringstream in(line);
        if (!(in >> count >> unit >> name))
            throw "bad line: " + line;
        for (std::string more; in >> more;)
            name += "-" + more;
        name = jut::txt::to_lower(name);
        std::cout << "count = " << count
            << ", unit = " << unit
            << ", name = " << name << '\n';
    }
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
