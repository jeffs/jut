/** @file app/jut-test-txt-print.cpp Test driver for component jut/txt/print. */

// Local
#include "jut/txt/print.hpp"

// C++ standard
#include <cassert>
#include <sstream>

int main() {
    { std::ostringstream s;
      jut::txt::print(s);
      assert(s.str() == "\n");
    }
    { std::ostringstream s;
      jut::txt::print(s, "hello");
      assert(s.str() == "hello\n");
    }
    { std::ostringstream s;
      jut::txt::print(s, "hello", "world");
      assert(s.str() == "hello world\n");
    }
}
