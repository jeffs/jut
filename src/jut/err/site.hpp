/** @file jut/err/site.hpp Exception annotated with throw site. */

#ifndef JUT_ERR_SITE_INCLUDED
#define JUT_ERR_SITE_INCLUDED

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
    auto const& jut_err_lhs = (LHS); \
    auto const& jut_err_rhs = (RHS); \
    if (jut_err_lhs != jut_err_rhs) \
        JUT_ERR_THROW_LOGIC(( \
                    jut::err::detail::assert_eq_format( \
                        jut_err_lhs, \
                        jut_err_rhs))) \
    else; \
}

#define JUT_ERR_THROW_RUNTIME(MESSAGE) \
    throw jut::err::site_runtime_error(MESSAGE, __FILE__, __LINE__);

#define JUT_ERR_CHECK(WHAT) if (!(WHAT)) { \
    JUT_ERR_THROW_RUNTIME("CHECK: " #WHAT) \
} else;

#define JUT_ERR_CHECK_EQ(LHS, RHS) { \
    auto const& jut_err_lhs = (LHS); \
    auto const& jut_err_rhs = (RHS); \
    if (jut_err_lhs != jut_err_rhs) \
        JUT_ERR_THROW_RUNTIME(( \
                    jut::err::detail::assert_eq_format( \
                        jut_err_lhs, \
                        jut_err_rhs))) \
    else; \
}

#define JUT_ERR_CHECK_POSIX(EXPR) [&] { \
    auto const& jut_err_result = (EXPR); \
    if (jut_err_result == \
            jut::err::detail::posix_error<decltype(EXPR)>::value) \
        JUT_ERR_THROW_RUNTIME((#EXPR " reported an error")) \
    return jut_err_result; \
}();


namespace jut { // Jeff's UTilitites
namespace err { // ERRor handling

namespace detail {

template <class T>
struct posix_error {
    static constexpr T value = static_cast<T>(-1);
};

template <class T>
struct posix_error<T*> {
    static constexpr T* value = nullptr;
};

/** @todo Print expressions, not values, of unprintable types. */
template <class L, class R>
std::string assert_eq_format(L const& lhs, R const& rhs) {
    std::ostringstream s;
    s << lhs << " != " << rhs;
    return s.str();
}

}   // detail

template <class E>
struct basic_site_error: E {

    friend
    std::ostream& operator<<(std::ostream& out, basic_site_error const& x) {
        return out << x.file << ':' << x.line << ": " << x.what();
    }

    std::string file;
    int         line;

    basic_site_error(
            std::string const& what,
            std::string const& file,
            int const          line):
        E(what),
        file(file),
        line(line) { }
};

using site_logic_error = basic_site_error<std::logic_error>;
using site_runtime_error = basic_site_error<std::runtime_error>;

std::ostream& operator<<(std::ostream&, site_logic_error const&);

}   // err
}   // jut

#endif
