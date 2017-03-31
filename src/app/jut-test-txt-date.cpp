/** @file app/jut-test-txt-date.cpp Test driver for jut/txt/date. */

#include "jut/txt/date.hpp"

// Local
#include "jut/err/site.hpp"

// C++ standard
#include <cassert>
#include <iostream>
#include <string>

namespace {

struct failure {
    std::string stamp;
};

struct at_most {

    char digit;

    explicit at_most(int const d):
        digit((assert(0 <= d), assert(d <= 9), '0' + d)) { }

    bool operator()(char const c) const {
        return '0' <= c && c <= digit;
    }
};

void verify(std::string const& s) {
    auto const expect = [&s](bool const b) {
        if (!b)
            throw failure{s};
    };
    expect(sizeof "YYYY-MM-DD" - 1 ==       s.size() );
    expect(at_most{9}(                      s[0]    ));
    expect(at_most{9}(                      s[1]    ));
    expect(at_most{9}(                      s[2]    ));
    expect(at_most{9}(                      s[3]    ));
    expect('-' ==                           s[4]     );
    expect(at_most{1}(                      s[5]    ));
    expect(at_most{s[5] == '0' ? 9 : 2}(    s[6]    ));
    expect('-' ==                           s[7]     );
    expect(at_most{3}(                      s[8]    ));
    expect(at_most{s[8] < '3' ? 9 : 1}(     s[9]    ));
}

bool is_leap(int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

int month_length(int const year, int const month) {
    switch (month) {
      case 1: return 31;
      case 2: return 28 + is_leap(year);
      case 3: return 31;
      case 4: return 30;
      case 5: return 31;
      case 6: return 30;
      case 7: return 31;
      case 8: return 31;
      case 9: return 30;
      case 10: return 31;
      case 11: return 30;
      case 12: return 31;
    }
    assert(false);
}

}   // namespace

int main() try {

    for (int year : { 0, 1066, 2000 })
        for (int month = 1; month <= 12; ++month)
            for (int day = 1; day <= month_length(year, month); ++day)
                verify(jut::txt::date_stamp(year, month, day));

    verify(jut::txt::date_stamp());

} catch (failure const x) {
    std::clog << "FAIL: \"" << x.stamp << "\"\n";
    return 1;
} catch (jut::err::site_error const& x) {
    std::clog << "error: " << x << '\n';
    return 2;
}
