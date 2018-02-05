#ifndef BASE64_UTILS_HPP_INCLUDED
#define BASE64_UTILS_HPP_INCLUDED

/**
 @file base64_utils.hpp
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

#include "JuceHeader.h"

namespace base64u
{
    //==============================================================================
    inline String toBase64url(const String& pString)
    {
        return Base64::toBase64(pString).replaceCharacters("+/", "-_").removeCharacters("=");
    }
    
    //==============================================================================
    inline String fromBase64 (const String& encoded)
    {
        MemoryOutputStream m (encoded.length()); // should be smaller
        bool ok = Base64::convertFromBase64 (m, encoded);
        jassert (ok);
        ignoreUnused (ok);
        return m.toString();
    }
    
    //==============================================================================
    inline String fromBase64url(const String& pString)
    {
        int lPadding;
        switch (pString.length() % 4)
        {
            case 0: lPadding = 0; break;
            case 1: lPadding = 3; break;
            case 2: lPadding = 2; break;
            case 3: lPadding = 1; break;
            default: lPadding = 0; jassertfalse; break;
        }
        String lCompleted = pString.replaceCharacters("-_", "+/");
        lCompleted.append("===", lPadding);
        return fromBase64(lCompleted);
    }
    
    //==============================================================================
    inline MemoryBlock binaryFromBase64(const String& encoded)
    {
        MemoryOutputStream m (encoded.length()); // should be smaller
        bool ok = Base64::convertFromBase64 (m, encoded);
        jassert (ok);
        ignoreUnused (ok);
        return m.getMemoryBlock();
    }
    
    //==============================================================================
    inline MemoryBlock binaryFromBase64url(const String& pString)
    {
        int lPadding;
        switch (pString.length() % 4)
        {
            case 0: lPadding = 0; break;
            case 1: lPadding = 3; break;
            case 2: lPadding = 2; break;
            case 3: lPadding = 1; break;
            default: lPadding = 0; jassertfalse; break;
        }
        String lCompleted = pString.replaceCharacters("-_", "+/");
        lCompleted.append("===", lPadding);
        return binaryFromBase64(lCompleted);
    }
}

#endif
