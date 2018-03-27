#ifndef FILESYSTEM_UTILS_HPP_INCLUDED
#define FILESYSTEM_UTILS_HPP_INCLUDED

/**
 @file filesystem_utils.hpp
 @author François Becker

MIT License

Copyright (c) 2017-2018 François Becker

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

#include "fbu/possible_error.hpp"
#include "fbu/string_utils.hpp"

#include <vector>
#include <string>
#include <regex>

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
        
        //==============================================================================
        // POSIX fully portable filename:
        // - alphanumeric plus . _ -
        // - the first character must not be an hyphen ("-").
        // - must not be empty
        // - must not be "." nor ".."
        // - unicity: case-insensitive.
        // ref: https://en.wikipedia.org/wiki/Filename
        inline bool isPOSIXFullyPortableFileName(const char* pFileName)
        {
            if (std::string(pFileName) == "." || std::string(pFileName) == "..")
            {
                return false;
            }
            std::regex r("[a-zA-Z0-9._][a-zA-Z0-9._\\-]*");
            return std::regex_match(pFileName, r);
        }
#if 0
        // TODO FIXME: create a unit test for this
        assert(std::regex_match("ehfindjfqnsdl872394kfnlze", r));
        assert(std::regex_match("._djfqklsdf-dksfqshdjfkl6736824_sdfhjslf.dfnsjdlf.skfhdls", r));
        assert(!std::regex_match("", r));
        assert(!std::regex_match("-hyphen.begin", r));
        assert(!std::regex_match("/test", r));
#endif
    }
}

#endif
