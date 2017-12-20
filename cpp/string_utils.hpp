#ifndef STRING_UTILS_HPP_INCLUDED
#define STRING_UTILS_HPP_INCLUDED

/**
 @file string_utils.hpp
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
#include <vector>
#include <sstream>

namespace su
{
    //==============================================================================
    inline void find_and_replace(std::string& source, std::string const& find, std::string const& replace)
    {
        for(std::string::size_type i = 0; (i = source.find(find, i)) != std::string::npos;)
        {
            source.replace(i, find.length(), replace);
            i += replace.length();
        }
    }
    
    //==============================================================================
    inline std::vector<std::string> string_split(std::string pString, const char* pDelimiter)
    {
        std::vector<std::string> strings;
        
        std::string::size_type pos = 0;
        std::string::size_type prev = 0;
        while ((pos = pString.find(pDelimiter, prev)) != std::string::npos)
        {
            strings.push_back(pString.substr(prev, pos - prev));
            prev = pos + 1;
        }
        
        // To get the last substring (or only, if delimiter is not found)
        strings.push_back(pString.substr(prev));
        
        return strings;
    }
    
    //==============================================================================
    template<typename T>
    const std::string convert_to_string(const T &v)
    {
        std::ostringstream ss;
        ss << v;
        return ss.str();
    };
    
    //==============================================================================
    inline bool hasEnding(const std::string& fullString, const std::string& ending)
    {
        return (fullString.length() >= ending.length())
            && (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    }
}

#endif
