#include "jut/txt/file.hpp"

// C++ Standard
#include <sstream>
#include <stdexcept>

namespace jut {

std::ifstream txt::open(std::string const& fname) {
    using namespace std::string_literals;
    std::ifstream file(fname, std::ios::binary);
    if (!file)
        throw std::runtime_error(fname + " is not a readable file"s);
    return file;
}

std::string txt::slurp(std::string const& fname) {
    std::ostringstream out;
    auto file = open(fname);
    out << file.rdbuf();
    return out.str();
}

std::vector<std::string> txt::slurp_lines(std::string const& fname) {
    std::vector<std::string> lines;
    auto file = open(fname);
    for (std::string line; getline(file, line);)
        lines.push_back(line);
    return lines;
}

}
