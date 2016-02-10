#include "jut/dat/either.hpp"

// C++ standard
#include <string>

using jut::dat::either;
using std::move;
using std::string;

struct copy_report {
    int copy_constructions = 0;
    int copy_assignments   = 0;
    int move_constructions = 0;
    int move_assignments   = 0;

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
        ++report.move_constructions;
        return *this;
    }

    copy_counter(copy_counter&& rhs):
        value(rhs.value),
        report(rhs.report) {
        ++report.move_constructions;
    }

    copy_counter& operator=(copy_counter&& rhs) & {
        assert(&report == &rhs.report);
        value = move(rhs.value);
        ++report.move_assignments;
        return *this;
    }
};

void test_make_left() {
    auto x = either<int, string>::make_left(42);
    assert(x.is_left());
    assert(x.left() == 42);
}

void test_make_right() {
    auto x = either<int, string>::make_right("hello");
    assert(x.is_right());
    assert(x.right() == "hello");
}

void test_default_constructor() {
    either<int, string> x;
    assert(x.is_left());
    assert(x.left() == 0);
}

void test_copy_constructor_left() {
    auto y = either<int, string>::make_left(42), x = y;
    assert(x.is_left());
    assert(x.left() == 42);
}

void test_copy_constructor_right() {
    auto y = either<int, string>::make_right("hello"), x = y;
    assert(x.is_right());
    assert(x.right() == "hello");
}

void test_copy_assignment_left_left() {
    auto x = either<int, string>::make_left(1);
    auto y = either<int, string>::make_left(2);
    x = y;
    assert(x.is_left());
    assert(x.left() == 2);
}

void test_copy_assignment_left_right() {
    auto x = either<int, string>::make_left(42);
    auto y = either<int, string>::make_right("hello");
    x = y;
    assert(x.is_right());
    assert(x.right() == "hello");
}

void test_copy_assignment_right_left() {
    auto x = either<int, string>::make_right("hello");
    auto y = either<int, string>::make_left(42);
    x = y;
    assert(x.is_left());
    assert(x.left() == 42);
}

void test_copy_assignment_right_right() {
    auto x = either<int, string>::make_right("hello");
    auto y = either<int, string>::make_right("world");
    x = y;
    assert(x.is_right());
    assert(x.right() == "world");
}

void test_move_constructor_left() {
    copy_report r;
    copy_counter c(42, r);
    auto y = either<copy_counter, string>::make_left(c);
    r.clear();
    either<copy_counter, string> x = move(y);
    assert(x.is_left());
    assert(x.left().value == 42);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 1);
    assert(r.move_assignments   == 0);
}

void test_move_constructor_right() {
    copy_report r;
    copy_counter c(42, r);
    auto y = either<string, copy_counter>::make_right(c);
    r.clear();
    either<string, copy_counter> x = move(y);
    assert(x.is_right());
    assert(x.right().value == 42);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 1);
    assert(r.move_assignments   == 0);
}

void test_move_assignment_left_left() {
    copy_report r;
    copy_counter c1(1, r), c2(2, r);
    auto x = either<copy_counter, string>::make_left(c1);
    auto y = either<copy_counter, string>::make_left(c2);
    r.clear();
    x = move(y);
    assert(x.is_left());
    assert(x.left().value == 2);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 0);
    assert(r.move_assignments   == 1);
}

void test_move_assignment_left_right() {
    copy_report r;
    copy_counter c(42, r);
    auto x = either<string, copy_counter>::make_left("hello");
    auto y = either<string, copy_counter>::make_right(c);
    r.clear();
    x = move(y);
    assert(x.is_right());
    assert(x.right().value == 42);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 1);
    assert(r.move_assignments   == 0);
}

void test_move_assignment_right_left() {
    copy_report r;
    copy_counter c(42, r);
    auto x = either<copy_counter, string>::make_right("hello");
    auto y = either<copy_counter, string>::make_left(c);
    r.clear();
    x = move(y);
    assert(x.is_left());
    assert(x.left().value == 42);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 1);
    assert(r.move_assignments   == 0);
}

void test_move_assignment_right_right() {
    copy_report r;
    copy_counter c1(1, r), c2(2, r);
    auto x = either<string, copy_counter>::make_right(c1);
    auto y = either<string, copy_counter>::make_right(c2);
    r.clear();
    x = move(y);
    assert(x.is_right());
    assert(x.right().value == 2);
    assert(r.copy_constructions == 0);
    assert(r.copy_assignments   == 0);
    assert(r.move_constructions == 0);
    assert(r.move_assignments   == 1);
}

int main() {

    test_make_left();
    test_make_right();
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

    // DESTROY
    //  - destroy left
    //  - destroy right
    //  - destroy left after move-from
    //  - destroy right after move-from

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
