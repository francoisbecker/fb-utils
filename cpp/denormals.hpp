#ifndef DENORMALS_HPP_INCLUDED
#define DENORMALS_HPP_INCLUDED

/**
 @file denormals.hpp
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

#ifdef __APPLE__
#define DENORMALS_USE_FENV 1
#define DENORMALS_USE_XMMINTRIN 0
#else
#define DENORMALS_USE_FENV 0
#define DENORMALS_USE_XMMINTRIN 1
#endif

#if DENORMALS_USE_FENV
#include <cfenv>
#endif

#if DENORMALS_USE_XMMINTRIN
#include <xmmintrin.h>
#endif

class ScopedDenormalKiller
{
public:
    ScopedDenormalKiller()
    : mAlreadyRestored(false)
    {
#if DENORMALS_USE_FENV
        fegetenv(&mSaveFENV);
        fesetenv(FE_DFL_DISABLE_SSE_DENORMS_ENV);
#endif
#if DENORMALS_USE_XMMINTRIN
        mSaveXMMINTRIN = _mm_getcsr();
        _mm_setcsr(mSaveXMMINTRIN | (1 << 15) | (1 << 6));
#endif
    }
    ~ScopedDenormalKiller()
    {
        restore();
    }
    void restore()
    {
        if (!mAlreadyRestored)
        {
#if DENORMALS_USE_FENV
            fesetenv(&mSaveFENV);
#endif
#if DENORMALS_USE_XMMINTRIN
            _mm_setcsr(mSaveXMMINTRIN);
#endif
            mAlreadyRestored = true;
        }
    }
private:
#if DENORMALS_USE_FENV
    fenv_t mSaveFENV;
#endif
#if DENORMALS_USE_XMMINTRIN
    int    mSaveXMMINTRIN;
#endif
    bool   mAlreadyRestored;
};

#endif
