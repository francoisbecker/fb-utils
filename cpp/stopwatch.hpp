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

class StopWatch
{
public:
    StopWatch(const std::string& pName)
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
    
    void display()
    {
        auto lDiff = mStop - mStart;
        std::cout << mName << ": " << std::chrono::duration <double, std::nano> (lDiff).count() << " ns" << std::endl;
    }
    
    void stopAndDisplay()
    {
        stop();
        display();
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

class StopWatchStarting
: public StopWatch
{
public:
    StopWatchStarting(const std::string& pName)
    : StopWatch(pName)
    {
        start();
    }
};

#endif
