/** @file jut/err/todo.hpp `TODO` macro that throws a `site_logic_error`.
 *
 * @todo If JUT ever depends on Boost, replace __func__ with
 * BOOST_CURRENT_FUNCTION.
 */

#ifndef JUT_ERR_TODO_INCLUDED
#define JUT_ERR_TODO_INCLUDED

// Local
#include "jut/err/site.hpp"

// C++ standard
#include <string>

// Clients may `#define TODO JUT_ERR_TODO`.
#define JUT_ERR_TODO JUT_ERR_THROW_LOGIC(std::string("TODO: ") + __func__)

#endif
