/** @file jut/err/error.hpp Custom exceptions and error-handling macros. */

#ifndef JUT_ERR_ERROR_INCLUDED
#define JUT_ERR_ERROR_INCLUDED

// C++ standard
#include <sstream>
#include <stdexcept>
#include <string>

#define JUT_ERR_THROW_LOGIC(MESSAGE) \
    throw jut::err::site_logic_error(MESSAGE, __FILE__, __LINE__);

#define JUT_ERR_ASSERT(WHAT) if (!(WHAT)) { \
    JUT_ERR_THROW_LOGIC("ASSERT: " #WHAT) \
} else;

#define JUT_ERR_ASSERT_EQ(LHS, RHS) { \
    auto const& lhs = (LHS); \
    auto const& rhs = (RHS); \
    if (lhs != rhs) \
        JUT_ERR_THROW_LOGIC((jut::err::detail::assert_eq_format(lhs, rhs))) \
    else; \
}

namespace jut { // Jeff's UTilitites
namespace err { // ERRor handling

namespace detail {

/** @todo Print expressions, not values, of unprintable types. */
template <class L, class R>
std::string assert_eq_format(L const& lhs, R const& rhs) {
    std::ostringstream s;
    s << lhs << " != " << rhs;
    return s.str();
}

}   // detail

/** See also JUT_ERR_THROW_LOGIC. */
struct site_logic_error: std::logic_error {

    std::string file;
    int         line;

    site_logic_error(
            std::string const& what,
            std::string const& file_,
            int const          line_):
        logic_error(what),
        file(file_),
        line(line_) { }
};

std::ostream& operator<<(std::ostream&, site_logic_error const&);

}   // err
}   // jut

#endif
