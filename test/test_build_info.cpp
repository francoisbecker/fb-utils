#include "fbu/build_info.hpp"

#include "tests_common.hpp"

CASE("Build Info")
{
    EXPECT(fbu::getBuildInfo().mDate == __DATE__);
    EXPECT(fbu::getBuildInfo().mTime == __TIME__);
#ifdef _DEBUG
    EXPECT(fbu::getBuildInfo().mRelease == "Debug");
#else
    EXPECT(fbu::getBuildInfo().mRelease == "Release");
#endif
}
