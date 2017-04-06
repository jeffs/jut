#include "jut/txt/split.hpp"

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace txt = jut::txt;

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

int main() {

    ifstream meta("meta.smoosh"), data("00000.smoosh");

    string line;
    getline(meta, line);   // skip the version header
    vector<vector<string>> rows;

    while (getline(meta, line)) {
        auto row = txt::split(line, ',');           assert(row.size() == 4);
        auto name = row.front();
        auto beg = stoul(row[2]), end = stoul(row[3]);

        ofstream out(name);
        for (data.seekg(beg); beg != end; ++beg)
            out.put(data.get());
    }

}
