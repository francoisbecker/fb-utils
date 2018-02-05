#ifndef FILESYSTEM_UTILS_HPP_INCLUDED
#define FILESYSTEM_UTILS_HPP_INCLUDED

/**
 @file filesystem_utils.hpp
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

#include "possible_error.hpp"
#include "string_utils.hpp"

#include <vector>
#include <string>

#include <dirent.h>

namespace fbu
{
    namespace filesystem
    {
        //==============================================================================
        /**
         Will be needed until C++17
         */
#ifdef _WIN32
        constexpr const char* separator = "\\";
#else
        constexpr const char* separator = "/";
#endif
        
        //==============================================================================
        inline PossibleError<std::vector<std::string> > listDir(const std::string& pPath, const std::string& pEnding = "")
        {
            DIR* lDir = opendir(pPath.c_str());
            if (!lDir)
            {
                return error(errno);
            }
            std::vector<std::string> lList;
            if (pEnding.empty())
            {
                while (struct dirent* lDirEntry = readdir(lDir))
                {
                    lList.push_back(lDirEntry->d_name);
                }
            }
            else
            {
                while (struct dirent* lDirEntry = readdir(lDir))
                {
                    std::string lEntryName = lDirEntry->d_name;
                    if (fbu::string::hasEnding(lEntryName, pEnding))
                    {
                        lList.push_back(lEntryName);
                    }
                }
            }
            closedir(lDir);
            return lList;
        }
    }
}

#endif
