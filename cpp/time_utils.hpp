#ifndef TIME_UTILS_HPP_INCLUDED
#define TIME_UTILS_HPP_INCLUDED

/**
 @file time_utils.hpp
 @author François Becker
 
MIT License

Copyright (c) 2015-2017 François Becker

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

#include <cassert>
#include <ctime>

namespace tu
{
    inline std::time_t timeFromYMDString(const char* pString)
    {
        // Time from YYYY-MM-DD
        int lYear, lMonth, lDay;
        sscanf(pString, "%d-%d-%d", &lYear, &lMonth, &lDay);
        struct tm t = {0};
        t.tm_year = lYear - 1900;
        t.tm_mon = lMonth - 1;
        t.tm_mday = lDay;
        t.tm_isdst = -1;
        return mktime(&t);
    }
    
    inline std::time_t timeFromYMDHMSString(const char* pString)
    {
        // Time from YYYY-mm-DD HH:MM:SS
        int lYear, lMonth, lDay, lHour, lMinute, lSecond;
        sscanf(pString, "%d-%d-%d %d:%d:%d", &lYear, &lMonth, &lDay, &lHour, &lMinute, &lSecond);
        struct tm t = {0};
        t.tm_year = lYear - 1900;
        t.tm_mon = lMonth - 1;
        t.tm_mday = lDay;
        t.tm_hour = lHour;
        t.tm_min = lMinute;
        t.tm_sec = lSecond;
        t.tm_isdst = -1;
        return mktime(&t);
    }
    
    inline std::time_t timeFromStringDate(const char *time)
    {
        char s_month[5];
        int month, day, year;
        struct tm t = {0};
        static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
        
        sscanf(time, "%s %d %d", s_month, &day, &year);
        
        month = (int)(strstr(month_names, s_month)-month_names)/3;
        
        t.tm_mon = month;
        t.tm_mday = day;
        t.tm_year = year - 1900;
        t.tm_isdst = -1;
        
        return mktime(&t);
    }
}

#endif
