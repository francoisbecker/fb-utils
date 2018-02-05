#ifndef STOPWATCH_HPP_INCLUDED
#define STOPWATCH_HPP_INCLUDED

/**
 @file stopwatch.hpp
 @author François Becker

MIT License

Copyright (c) 2017 François Becker

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

#include <string>
#include <iostream>
#include <chrono>

/**
 @class StopWatch
 @brief Chronometer class. Has optionally a name and provides the method for
        displaying the duration between the start() and stop() calls.
 */
class StopWatch
{
protected:
    typedef std::ratio<1LL, 1LL> default_timeunit;
    
    template <typename TIMEUNIT>
    const char* timeunit()
    {
        switch (TIMEUNIT::den)
        {
            case 1000000000LL:
                return "ns";
            case 1000000LL:
                return "us";
            case 1000LL:
                return "ms";
            case 1LL:
                if (TIMEUNIT::num == 1LL)
                {
                    return "s";
                }
            default:
                return "?";
        }
    }
    
public:
    StopWatch(const std::string& pName = "")
    : mName(pName)
    {
    }
    
    void start()
    {
        mStart = std::chrono::steady_clock::now();
    }
    
    void stop()
    {
        mStop = std::chrono::steady_clock::now();
    }
    
    template <typename TIMEUNIT = default_timeunit>
    void display(std::ostream& pOutputStream = std::cout)
    {
        auto lDiff = mStop - mStart;
        if (!mName.empty())
        {
            pOutputStream << mName << ": ";
        }
        pOutputStream << std::chrono::duration<double, TIMEUNIT>(lDiff).count()
                      << " " << timeunit<TIMEUNIT>() << std::endl;
    }
    
    template <typename TIMEUNIT = default_timeunit>
    void stopAndDisplay()
    {
        stop();
        display<TIMEUNIT>();
    }
    
    void rename(const std::string& pName)
    {
        mName = pName;
    }
    
    void renameAndStart(const std::string& pName)
    {
        rename(pName);
        start();
    }
    
protected:
    std::string mName;
    std::chrono::steady_clock::time_point mStart;
    std::chrono::steady_clock::time_point mStop;
};

/**
 @class StopWatchStarted
 @brief A StopWatch that is started as soon as it is intantiated.
 */
class StopWatchStarted
: public StopWatch
{
public:
    StopWatchStarted(const std::string& pName = "")
    : StopWatch(pName)
    {
        start();
    }
};

#endif
