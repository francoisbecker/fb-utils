#include "tests_common.hpp"

lest::tests& specification()
{
    static lest::tests tests;
    return tests;
}

#if 0
CASE( "A passing test" "[pass]" )
{
    EXPECT( 42 == 42 );
}

CASE( "A failing test" "[fail]" )
{
    EXPECT( 42 == 7 );
}
#endif

int main(int argc, char* argv[])
{
    std::cout << "Running fb-utils tests..." << std::endl;
    auto lReturn = lest::run( specification(), argc, argv /*, std::cout */ );
    std::cout << "Done." << std::endl;
    return lReturn;
}

