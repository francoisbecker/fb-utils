#include "fbu/filesystem_utils.hpp"

#include "tests_common.hpp"

CASE( "fbu::filesystem::isPOSIXFullyPortableFileName()" )
{
    EXPECT( fbu::filesystem::isPOSIXFullyPortableFileName("ehfindjfqnsdl872394kfnlze") );
    EXPECT( fbu::filesystem::isPOSIXFullyPortableFileName("._djfqklsdf-dksfqshdjfkl6736824_sdfhjslf.dfnsjdlf.skfhdls") );
    EXPECT( ! fbu::filesystem::isPOSIXFullyPortableFileName("") );
    EXPECT( ! fbu::filesystem::isPOSIXFullyPortableFileName("-hyphen.begin") );
    EXPECT( ! fbu::filesystem::isPOSIXFullyPortableFileName("/test") );
}
