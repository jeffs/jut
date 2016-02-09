#include "jut/err/error.hpp"

namespace jut {

std::ostream& err::operator<<(std::ostream& out, site_logic_error const& x) {
    return out << x.file << ':' << x.line << ": " << x.what();
}

}   // jut
