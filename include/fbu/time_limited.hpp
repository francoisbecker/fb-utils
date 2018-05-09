#ifndef TIME_LIMITED_HPP_INC
#define TIME_LIMITED_HPP_INC

/**
 @file time_limited.hpp
 @author François Becker
 
MIT License

Copyright (c) 2016-2017 François Becker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "JuceHeader.h"

#include "fbu/build_info.hpp"

#include "fbu/time_utils.hpp"

/**
 @class TimeLimitedFromBuild
 */
template <int DAYSAFTERBUILD>
class TimeLimitedFromBuild
{
public:
    TimeLimitedFromBuild()
    : mLimit(fbu::time::timeFromStringDate(fbu::getBuildInfo().mDate.c_str()) + DAYSAFTERBUILD * 24 * 3600)
    , mIsOutdatedCached(isOutdated())
    {
    }
    
    String getTimeLimit() const
    {
        return std::ctime(&mLimit);
    }
    
    bool isOutdated() const
    {
        std::time_t lNow = std::time(nullptr);
        return difftime(lNow, mLimit) > 0.;
    }
    
    bool isOutdatedCached() const
    {
        return mIsOutdatedCached;
    }
    
    int getRemainingDays() const
    {
        std::time_t lNow = std::time(nullptr);
        return (int)(- difftime(lNow, mLimit) / (24 * 3600));
    }
    
private:
    std::time_t mLimit;
    bool        mIsOutdatedCached;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeLimitedFromBuild)
};

/**
 @class TimeLimitedFromFirstRun
 */
template <int DAYSAFTERFIRSTRUN>
class TimeLimitedFromFirstRun
{
public:
    TimeLimitedFromFirstRun(const String& pCompanyName, const String& pSKU, const String& pVersion, bool pCommonToAllUsers)
    : mLimit()
    {
        String lVersion(pVersion.replaceCharacters(".", "p"));
        
        PropertiesFile::Options lOptions;
        lOptions.applicationName = String(".") + pSKU;
        lOptions.filenameSuffix = "bin";
        lOptions.folderName = pCompanyName;
        lOptions.osxLibrarySubFolder = "Application Support";
        lOptions.commonToAllUsers = pCommonToAllUsers;
        lOptions.ignoreCaseOfKeyNames = false;
        lOptions.doNotSave = false;
        lOptions.millisecondsBeforeSaving = 0;
        lOptions.storageFormat = PropertiesFile::storeAsCompressedBinary;
        ScopedPointer<PropertiesFile> lSettings = new PropertiesFile(lOptions);
        
        String lLimitString = lSettings->getValue(lVersion, "");
        if (lLimitString.isEmpty())
        {
            std::time_t lNow = std::time(nullptr);
            mLimit = lNow + DAYSAFTERFIRSTRUN * 24 * 3600;
            lSettings->setValue(lVersion, String((long)mLimit));
        }
        else
        {
            mLimit = (long)lLimitString.getDoubleValue(); // TODO: something more direct
        }
    }
    
    String getTimeLimit() const
    {
        return std::ctime(&mLimit);
    }
    
    bool isOutdated() const
    {
        std::time_t lNow = std::time(nullptr);
        return difftime(lNow, mLimit) > 0.;
    }
    
private:
    std::time_t                   mLimit;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeLimitedFromFirstRun)
};

#endif
