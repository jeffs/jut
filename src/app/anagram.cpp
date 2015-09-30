// Prints anagrams of words provided as command-line arguments.
//
// TODO Cache buckets.
// TODO Accept word-file as a flag parameter.

#define TODO throw std::logic_error("TODO");

#include "jut/txt/file.hpp"
#include "jut/txt/roll.hpp"
#include "jut/txt/split.hpp"

// C++ Standard
#include <chrono>
#include <exception>
#include <iostream>
#include <unordered_map>

namespace {

namespace txt = jut::txt;

using namespace std::literals;

using bucket_map = std::unordered_map<std::string, std::vector<std::string>>;

auto sorted(std::string word) {
    std::sort(begin(word), end(word));
    return word;
}

auto make_buckets(std::string const& word_file_name) {
    bucket_map buckets;
    for (auto const& word : txt::slurp_lines(word_file_name))
        buckets[sorted(word)].push_back(word);
    return buckets;
}

void save_buckets(bucket_map const& buckets, std::string const& fname) {
    auto file = txt::open(fname, std::ios_base::out);
    for (auto const& kv : buckets) {
        file << kv.first << '\n';
        for (auto const& word : kv.second)
            file << word << '\n';
        file << '\n';
    }
}

auto load_buckets_imp(std::istream& in) {
    bucket_map buckets;
    for (std::string line, key; getline(in, line);)
        if (line.empty())       key.clear();
        else if (key.empty())   key = line;
        else                    buckets[key].push_back(line);
    return buckets;
}

auto load_buckets(
        std::string const& bucket_file_name,
        std::string const& word_file_name) try {
    auto file = txt::open(bucket_file_name);
    return load_buckets_imp(file);
} catch (txt::open_error const&) {
    save_buckets(make_buckets(word_file_name), bucket_file_name);
    auto file = txt::open(bucket_file_name);
    return load_buckets_imp(file);
}

}

int main(int argc, char const** argv) try {
    auto bucket_file_name = "/tmp/jut-buckets.txt";
    auto word_file_name = "/usr/share/dict/words";
    auto buckets = load_buckets(bucket_file_name, word_file_name);
    auto want_roll = argc > 1 && (argv[1] == "--roll"s || argv[1] == "-r"s);
    if (want_roll) ++argv;
    while (auto word = *++argv)
        for (auto const& anagram : buckets[sorted(word)])
            if (want_roll) txt::roll(anagram + '\n', std::cout, 10ms);
            else std::cout << anagram << '\n';
} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
