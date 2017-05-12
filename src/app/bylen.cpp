#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <unordered_set>
#include <string>

template <class K, class V> using Map = std::map<K, V>;
template <class T> using Set = std::unordered_set<T>;

using File = std::ifstream;
using Size = std::size_t;
using String = std::string;

int main(int argc, char** argv) {
    Map<Size, Set<String>> uniques;
    Map<Size, Size> counts;

    while (auto path = *++argv) {
        File in(path);

        for (String line; getline(in, line);) {
            auto const length = line.length();
            uniques[length].insert(line);
            ++counts[length];
        }

        if (!in.eof()) {
            std::cerr << "error: can't read " << path << '\n';
            return 1;
        }
    }

    for (auto&& [length, lines] : uniques) {
        auto const total = counts[length], unique = lines.size();
        std::cout << length << '\t' << total << '\t' << unique << '\n';
    }
}
