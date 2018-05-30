#ifndef TESTS_COMMON_HPP_INCLUDED
#define TESTS_COMMON_HPP_INCLUDED

#define lest_FEATURE_AUTO_REGISTER 1
#include "lest.hpp"

#undef CASE
#define CASE( name ) lest_CASE( specification(), name )

extern lest::tests & specification();

#endif

