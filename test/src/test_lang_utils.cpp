#include "fbu/lang_utils.hpp"

#include "tests_common.hpp"

CASE( "fbu::lang::OnCopy" )
{
    int lCounter = 0;
    fbu::lang::OnCopyFunction lOCF([&](){ ++lCounter; });
    auto lOther = lOCF;
    EXPECT(lCounter == 1);
    auto& lRefToOther = lOther; // no copy
    EXPECT(lCounter == 1);
    auto lAnother = lRefToOther;
    EXPECT(lCounter == 2);
}
