#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<std::string>> read_paragraphs(std::istream& in) {
    std::locale loc;
    std::vector<std::vector<std::string>> paragraphs{{}};
    for (std::string line; getline(in, line);) {
        if (line.empty() || std::isspace(line.front(), loc))
            paragraphs.back().push_back(std::move(line));
        else
            paragraphs.push_back({std::move(line)});
    }
    paragraphs.erase(
            std::remove_if(
                paragraphs.begin(), paragraphs.end(),
                [](auto const& para) { return para.empty(); }));
    return paragraphs;
}

void process(std::istream& in) {
    auto paragraphs = read_paragraphs(in);
    std::sort(paragraphs.begin(), paragraphs.end());
    for (auto const& para : paragraphs) {
        for (auto const& line : para)
            std::cout << line << '\n';
    }
}

void process_file(char const* fname) {
    std::ifstream file(fname);
    process(file);
}

int main(int argc, char** argv) {
    if (argc < 2)
        process(std::cin);
    else
        std::for_each(&argv[1], &argv[argc], process_file);
}
