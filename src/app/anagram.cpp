/** @file anagram.cpp Prints anagrams of words specified on command line.
 *
 * @todo Accept word-file as a flag parameter.
 */

// Local
#include "jut/txt/file.hpp"
#include "jut/txt/roll.hpp"
#include "jut/txt/split.hpp"

// C++ standard
#include <algorithm>
#include <chrono>
#include <exception>
#include <iostream>
#include <locale>
#include <unordered_map>

namespace {

namespace txt = jut::txt;

using namespace std::literals;

using std::string;

using string_vec = std::vector<string>;
using bucket_map = std::unordered_map<string, string_vec>;

auto lower_cased(string word) {
    std::transform(begin(word), end(word), begin(word),
            [](char c) { return std::tolower(c, std::locale()); });
    return word;
}

auto sorted(string word) {
    std::sort(begin(word), end(word));
    return word;
}

auto get_key(string const& word) {
    return sorted(lower_cased(word));
}

auto make_buckets(string const& word_file_name) {
    bucket_map buckets;
    for (auto const& word : txt::slurp_lines(word_file_name))
        buckets[get_key(word)].push_back(word);
    return buckets;
}

void save_buckets(bucket_map const& buckets, string const& fname) {
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
    for (string line, key; getline(in, line);)
        if (line.empty())       key.clear();
        else if (key.empty())   key = line;
        else                    buckets[key].push_back(line);
    return buckets;
}

auto load_buckets(
        string const& bucket_file_name,
        string const& word_file_name) try {
    auto file = txt::open(bucket_file_name);
    return load_buckets_imp(file);
} catch (txt::open_error const&) {
    save_buckets(make_buckets(word_file_name), bucket_file_name);
    auto file = txt::open(bucket_file_name);
    return load_buckets_imp(file);
}

struct arg_set {
    bool       want_roll;
    string_vec words;
};

arg_set parse_args(int argc, char const** argv) {
    bool got_flag = argv[1] && (argv[1] == "--roll"s || argv[1] == "-r"s);
    return {got_flag, string_vec(argv + (got_flag ? 2 : 1), argv + argc)};
}

}

/** Prints anagrams of each element of `argv`. */
int main(int argc, char const** argv) try {

    // Parse command-line arguments.
    auto args = parse_args(argc, argv);
    auto print = args.want_roll
        ? [](string const& line) { txt::roll(line + '\n', std::cout, 10ms); }
        : [](string const& line) { std::cout << line << '\n'; };

    // Load all known words.
    auto bucket_file_name = "/tmp/jut-buckets.txt";
    auto word_file_name = "/usr/share/dict/words";
    auto buckets = load_buckets(bucket_file_name, word_file_name);

    // Print all known anagrams of each specified word.
    for (auto const& word : args.words)
        for (auto const& anagram : buckets[get_key(word)])
            print(anagram);

} catch (std::exception const& x) {
    std::cerr << "error: " << x.what() << '\n';
    return -1;
}
