#include "jut/txt/roll.hpp"

// C++ Standard
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <thread>

namespace jut {

namespace {

using std::begin;
using std::end;

char const letters[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

}

void txt::roll(
        std::string const&         line,
        std::ostream&              out,
        std::chrono::milliseconds  period) {
    std::string s;
    for (char c : line) {
        if (std::find(begin(letters), end(letters), c) == end(letters)) {
            s.push_back(c);
            out << '\r' << s << std::flush;
        } else {
            for (char d : letters) {
                s.push_back(d);
                out << '\r' << s << std::flush;
                std::this_thread::sleep_for(period);
                if (c == d)
                    break;
                s.pop_back();
            }
        }
    }
}

void txt::roll(
        std::istream&              in,
        std::ostream&              out,
        std::chrono::milliseconds  period) {
    for (std::string line; getline(in, line);) {
        txt::roll(line, out, period);
        out << '\n';
    }
}

}
