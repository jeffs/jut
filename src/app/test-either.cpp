#include "jut/dat/either.hpp"

// C++ standard
#include <string>

using jut::dat::either;

int main() {

    // can we CONTSRUCT an either
    //  - left from lvalue
    //  - right from lvalue
    //  - left from rvalue
    //  - right from rvalue

    // make_left(L const& value);
    // make_right(R const& value);

    // either(either const& rhs);
    // either(either&& rhs);

    // ~either();
    // operator=(either const& rhs);
    // operator=(either&& rhs);

    // is_left() const;
    // is_right() const;
    // left() const;
    // right() const;
    // leftp() const;
    // rightp() const;

    auto left = either<int, std::string>::make_left(42);
    assert(left.is_left());
    assert(left.left() == 42);
}
