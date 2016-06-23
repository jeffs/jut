/** @file pork.cpp Purely functional Pig Latin.
 *
 * \code{.sh}
 * $ clang++ -o pork -std=c++14 -pedantic -Wall pork.cpp
 * $ ./pork hello world
 * ellohay orldway
 * \endcode
 *
 * @todo Preserve case.
 * @todo Respect punctuation.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

/** English consonants and consonant clusters, longest first.
 *
 * @see http://www.enchantedlearning.com/consonantblends/
 */
std::array<std::string, 56> const clusters = {{
    "sch", "scr", "shr", "sph", "spl", "spr", "squ", "str", "thr" "bl", "br",
    "ch",  "cl",  "cr",  "dr",  "fl",  "fr",  "gl",  "gr",  "pl", "pr", "sc",
    "sh",  "sk",  "sl",  "sm",  "sn",  "sp",  "st",  "sw",  "th", "tr", "tw",
    "wh",  "wr", "b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p",
    "q", "r", "s", "t", "v", "w", "x", "y", "z"
}};

/** An empty string that can be returned by reference. */
std::string const empty;

/** Returns true if the `needle` is a prefix of `haystack`. */
bool has_prefix(std::string const& haystack, std::string const& needle) {
    auto e = end(needle);
    return std::mismatch(begin(needle), e, begin(haystack)).first == e;
}

/** Returns the leading consonant cluster of `word`, or an empty string if
 * `word` does not begin with a consonant.
 */
std::string const& leading_consonants(std::string const& word) {
    auto ec = end(clusters);
    auto f = [&word](auto const& s) { return has_prefix(word, s); };
    auto p = std::find_if(begin(clusters), ec, f);
    return p == ec ? empty : *p;
}

/** Returns the Pig Latin translation of the specified `word`. */
std::string pork(std::string word) {
    auto s = leading_consonants(word);
    return s.empty() ? word + "way" : word.substr(s.size()) + s + "ay";
}

/** Converts each word in `argv` to Pig Latin. */
int main(int argc, char** argv) {
    std::ostream_iterator<std::string> out(std::cout, " ");
    std::transform(argv + 1, argv + argc, out, pork);
    std::cout << '\n';
}
