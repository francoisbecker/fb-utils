#include "fbu/filesystem_utils.hpp"

#include "tests_common.hpp"

CASE( "fbu::fs::isPOSIXFullyPortableFileName()" )
{
    EXPECT( fbu::fs::isPOSIXFullyPortableFileName("ehfindjfqnsdl872394kfnlze") );
    EXPECT( fbu::fs::isPOSIXFullyPortableFileName("._djfqklsdf-dksfqshdjfkl6736824_sdfhjslf.dfnsjdlf.skfhdls") );
    EXPECT( ! fbu::fs::isPOSIXFullyPortableFileName("") );
    EXPECT( ! fbu::fs::isPOSIXFullyPortableFileName("-hyphen.begin") );
    EXPECT( ! fbu::fs::isPOSIXFullyPortableFileName("/test") );
}

CASE("fbu::fs::setFileContents() and fbu::fs::getFileContents()")
{
    std::string lTestPath = "/tmp/lorem.test.txt";
    std::string lFileContents = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    EXPECT( fbu::fs::setFileContents(lTestPath.c_str(), lFileContents.c_str()) );

    // TODO: test failure

    auto lRecoveredPE = fbu::fs::getFileContents("/tmp/lorem.test.txt");
    EXPECT( lRecoveredPE );
    EXPECT( lRecoveredPE() == lFileContents );
    
    // TODO: test failure
}
