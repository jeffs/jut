// This program prints multiple events per second of a single day.  Events are
// evenly distributed in two dimensions: one of low cardinality, the other
// high.

#include <cstdio>

int const lo = 2, hi = 1000;    // cardinalities
int const eps = 100;            // events per second

char const format[] = "2017-03-17T%02d:%02d:%02d\tlo%d\thi%d\t3.14159\n";

int main() {
    for (int h = 0; h < 24; ++h)
        for (int m = 0; m < 60; ++m)
            for (int s = 0; s < 60; ++s)
                for (int i = 0; i < eps; ++i)
                    std::printf(format, h, m, s, i % lo, i % hi);
}
