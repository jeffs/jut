/** @file app/jut-test-dat-either.cpp Test driver for jut/test/dat/either. */

#include "jut/dat/either.hpp"

// C++ standard
#include <string>

using jut::dat::either;
using std::string;

struct copy_report {
    int copy_constructions = 0;
    int copy_assignments   = 0;
    int move_constructions = 0;
    int move_assignments   = 0;
    int destructions       = 0;

    void clear() { *this = copy_report{}; }
};

struct copy_counter {

    int          value;
    copy_report& report;

    copy_counter(int value_, copy_report& report_):
        value(value_),
        report(report_) { }

    copy_counter(copy_counter const& rhs):
        value(rhs.value),
        report(rhs.report) {
        ++report.copy_constructions;
    }

    copy_counter& operator=(copy_counter const& rhs) & {
        assert(&report == &rhs.report);
        value = rhs.value;
        ++report.copy_assignments;
        return *this;
    }

    copy_counter(copy_counter&& rhs):
        value(rhs.value),
        report(rhs.report) {
        ++report.move_constructions;
    }

    copy_counter& operator=(copy_counter&& rhs) & {
        assert(&report == &rhs.report);
        value = std::move(rhs.value);
        ++report.move_assignments;
        return *this;
    }

    ~copy_counter() { ++report.destructions; }
};

struct copy_fixture: copy_report {
    copy_counter counter1, counter2;

    copy_fixture(): copy_report(), counter1(1, *this), counter2(2, *this) { }
};

void test_make_left_copy() {
    copy_fixture f;
    {
        auto x = either<copy_counter, int>::make_left(f.counter1);
        assert(x.is_left());
        assert(x.left().value == 1);
    }
    assert(f.copy_constructions == 1);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 1);
}

void test_make_left_move() {
    copy_fixture f;
    {
        auto x = either<copy_counter, int>::make_left(std::move(f.counter1));
        assert(x.is_left());
        assert(x.left().value == 1);
    }
    assert(f.copy_constructions == 0);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 1);
}

void test_make_right_copy() {
    copy_fixture f;
    {
        auto x = either<int, copy_counter>::make_right(f.counter1);
        assert(x.is_right());
        assert(x.right().value == 1);
    }
    assert(f.copy_constructions == 1);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 1);
}

void test_make_right_move() {
    copy_fixture f;
    {
        auto x = either<int, copy_counter>::make_right(std::move(f.counter1));
        assert(x.is_right());
        assert(x.right().value == 1);
    }
    assert(f.copy_constructions == 0);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 1);
}

namespace test_default_constructor_imp {

    copy_report left_report, right_report;

    struct left_counter: copy_counter {
        left_counter(): copy_counter(1, left_report) { }
    };

    struct right_counter: copy_counter {
        right_counter(): copy_counter(2, right_report) { }
    };
}

/** @note This function should not be called more than once per process. */
void test_default_constructor() {
    namespace imp = test_default_constructor_imp;
    {
        either<imp::left_counter, imp::right_counter> x;
        assert(x.is_left());
        assert(x.left().value == 1);
    }
    assert(imp::left_report.copy_constructions  == 0);
    assert(imp::left_report.copy_assignments    == 0);
    assert(imp::left_report.move_constructions  == 0);
    assert(imp::left_report.move_assignments    == 0);
    assert(imp::left_report.destructions        == 1);
    assert(imp::right_report.copy_constructions == 0);
    assert(imp::right_report.copy_assignments   == 0);
    assert(imp::right_report.move_constructions == 0);
    assert(imp::right_report.move_assignments   == 0);
    assert(imp::right_report.destructions       == 0);
}

void test_copy_constructor_left() {
    copy_fixture f;
    {
        auto y = either<copy_counter, string>::make_left(f.counter1), x = y;
        assert(x.is_left());
        assert(x.left().value == 1);
    }
    assert(f.copy_constructions == 2);  // copied into y, copied into x
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);
}

void test_copy_constructor_right() {
    copy_fixture f;
    {
        auto y = either<string, copy_counter>::make_right(f.counter2), x = y;
        assert(x.is_right());
        assert(x.right().value == 2);
    }
    assert(f.copy_constructions == 2);  // copied into y, copied into x
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);
}

void test_copy_assignment_left_left() {
    copy_fixture f;
    {
        auto x = either<copy_counter, int>::make_left(f.counter1);
        auto y = either<copy_counter, int>::make_left(f.counter2);
        x = y;
        assert(x.is_left());
        assert(x.left().value == 2);
        assert(y.is_left());
        assert(y.left().value == 2);
    }
    assert(f.copy_constructions == 2);  // copied into x, copied into y
    assert(f.copy_assignments   == 1);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);
}

void test_copy_assignment_left_right() {
    copy_fixture f;
    {
        auto x = either<copy_counter, copy_counter>::make_left(f.counter1);
        auto y = either<copy_counter, copy_counter>::make_right(f.counter2);
        x = y;
        assert(x.is_right());
        assert(x.right().value == 2);
        assert(y.is_right());
        assert(y.right().value == 2);
    }
    assert(f.copy_constructions == 3);  // x.left, y.right, x.right
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 3);  // x.left, y.right, x.right
}

void test_copy_assignment_right_left() {
    copy_fixture f;
    {
        auto x = either<copy_counter, copy_counter>::make_right(f.counter1);
        auto y = either<copy_counter, copy_counter>::make_left(f.counter2);
        x = y;
        assert(x.is_left());
        assert(x.left().value == 2);
        assert(y.is_left());
        assert(y.left().value == 2);
    }
    assert(f.copy_constructions == 3);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 3);
}

void test_copy_assignment_right_right() {
    copy_fixture f;
    {
        auto x = either<int, copy_counter>::make_right(f.counter1);
        auto y = either<int, copy_counter>::make_right(f.counter2);
        x = y;
        assert(x.is_right());
        assert(x.right().value == 2);
        assert(y.is_right());
        assert(y.right().value == 2);
    }
    assert(f.copy_constructions == 2);
    assert(f.copy_assignments   == 1);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);
}

void test_move_constructor_left() {
    copy_fixture f;
    {
        auto y = either<copy_counter, string>::make_left(f.counter1);
        auto x = std::move(y);
        assert(x.is_left());
        assert(x.left().value == 1);
    }
    assert(f.copy_constructions == 1);  // into y
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);  // into x
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);  // x.left(), y.left()
}

void test_move_constructor_right() {
    copy_fixture f;
    {
        auto y = either<string, copy_counter>::make_right(f.counter1);
        auto x = std::move(y);
        assert(x.is_right());
        assert(x.right().value == 1);
    }
    assert(f.copy_constructions == 1);  // into y
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);  // into x
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 2);  // x.right(), y.right()
}

void test_move_assignment_left_left() {
    copy_fixture f;
    {
        auto x = either<copy_counter, string>::make_left(f.counter1);
        auto y = either<copy_counter, string>::make_left(f.counter2);
        x = std::move(y);
        assert(x.is_left());
        assert(x.left().value == 2);
    }
    assert(f.copy_constructions == 2);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 1);
    assert(f.destructions       == 2);
}

void test_move_assignment_left_right() {
    copy_fixture f;
    {
        auto x = either<copy_counter, copy_counter>::make_left(f.counter1);
        auto y = either<copy_counter, copy_counter>::make_right(f.counter2);
        x = std::move(y);
        assert(x.is_right());
        assert(x.right().value == 2);
    }
    assert(f.copy_constructions == 2);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 3);
}

void test_move_assignment_right_left() {
    copy_fixture f;
    {
        auto x = either<copy_counter, copy_counter>::make_right(f.counter1);
        auto y = either<copy_counter, copy_counter>::make_left(f.counter2);
        x = std::move(y);
        assert(x.is_left());
        assert(x.left().value == 2);
    }
    assert(f.copy_constructions == 2);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 1);
    assert(f.move_assignments   == 0);
    assert(f.destructions       == 3);
}

void test_move_assignment_right_right() {
    copy_fixture f;
    {
        auto x = either<string, copy_counter>::make_right(f.counter1);
        auto y = either<string, copy_counter>::make_right(f.counter2);
        x = std::move(y);
        assert(x.is_right());
        assert(x.right().value == 2);
    }
    assert(f.copy_constructions == 2);
    assert(f.copy_assignments   == 0);
    assert(f.move_constructions == 0);
    assert(f.move_assignments   == 1);
    assert(f.destructions       == 2);
}

int main() {

    // static functions
    test_make_left_copy();
    test_make_left_move();
    test_make_right_copy();
    test_make_right_move();

    // special member functions
    test_default_constructor();
    test_copy_constructor_left();
    test_copy_constructor_right();
    test_copy_assignment_left_left();
    test_copy_assignment_left_right();
    test_copy_assignment_right_left();
    test_copy_assignment_right_right();
    test_move_constructor_left();
    test_move_constructor_right();
    test_move_assignment_left_left();
    test_move_assignment_left_right();
    test_move_assignment_right_left();
    test_move_assignment_right_right();

    // MANIPULATE
    //  - left on rvalue
    //  - right on rvalue
    //  - leftp
    //  - rightp

    // ACCESS
    //  - is_left on const
    //  - is_right on const
    //  - left on const
    //  - right on const
    //  - leftp on const
    //  - rightp on const

}
