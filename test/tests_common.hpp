#ifndef TESTS_COMMON_HPP_INCLUDED
#define TESTS_COMMON_HPP_INCLUDED

#include "lest.hpp"

#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

#endif

