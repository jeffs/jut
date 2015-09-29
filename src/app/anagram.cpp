// Prints anagrams of words provided as command-line arguments.
//
// TODO Cache buckets.
// TODO Accept word-file as a flag parameter.

#include "jut/txt/file.hpp"
#include "jut/txt/split.hpp"

// C++ Standard
#include <exception>
#include <iostream>
#include <unordered_map>

namespace {

namespace txt = jut::txt;

auto sorted(std::string word) {
    std::sort(begin(word), end(word));
    return word;
}

auto make_buckets(std::string const& word_file_name) {
    std::unordered_map<std::string, std::vector<std::string>> buckets;
    for (auto const& word : txt::slurp_lines(word_file_name))
        buckets[sorted(word)].push_back(word);
    return buckets;
}

}

int main(int argc, char const** argv) try {
    auto buckets = make_buckets("/usr/share/dict/words");
    while (auto word = *++argv)
        for (auto const& anagram : buckets[sorted(word)])
            std::cout << anagram << '\n';
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
