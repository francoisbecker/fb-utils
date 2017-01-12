#ifndef MATH_UTILS_HPP_INCLUDED
#define MATH_UTILS_HPP_INCLUDED

/**
 @file math_utils.hpp
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

#include "math_float_constants.hpp"

#include <cassert>

#define DEG2RAD (M_PI / 180.)
#define DEG2RADf (M_PIf / 180.f)
#define RAD2DEG (180. / M_PI)
#define RAD2DEGf (180.f / M_PIf)

namespace mu
{
    //==============================================================================
    template <typename T>
    T finvsqrt(T x)
    {
        assert(x >= (T)0); // caller is responsible for checking that
        return (T)1 / std::sqrt(x);
    }
    /*template <>
     float finvsqrt(float x)
     {
     long i;
     float x2, y;
     const float threehalfs = 1.5F;
     
     x2 = x * 0.5F;
     y  = x;
     i  = * ( long * ) &y;                       // evil floating point bit level hacking
     i  = 0x5f3759df - ( i >> 1 );               // what the?
     y  = * ( float * ) &i;
     y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
     //	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
     
     return y;
     } // see https://en.wikipedia.org/wiki/Fast_inverse_square_root
     // TODO: unit tests!
     */
    
    
    //==============================================================================
    inline bool isDomainAngle(float pAngle)
    {
        return ((pAngle > - M_PIf) && (pAngle <= M_PIf));
    }
    
    //==============================================================================
    inline bool isDomainAnglePermissive(float pAngle)
    {
        return ((pAngle >= - M_PIf) && (pAngle <= M_PIf));
    }
    
    //==============================================================================
    /**
     Get an angle in the domain )-π,π) provided the input is in the domain )-3π,3π)
     */
    inline float domainAngleSimple(float pAngle)
    {
        if (pAngle > M_PIf)
        {
            pAngle -= 2.f * M_PIf;
        }
        else if (pAngle <= - M_PIf)
        {
            pAngle += 2.f * M_PIf;
        }
        assert(isDomainAngle(pAngle));
        return pAngle;
    }
    
    //==============================================================================
    inline float domainAngle(float pAngle)
    {
        while (pAngle > M_PIf)
        {
            pAngle -= 2.f * M_PIf;
        }
        while (pAngle <= - M_PIf)
        {
            pAngle += 2.f * M_PIf;
        }
        assert(isDomainAngle(pAngle));
        return pAngle;
    }
    
    //==============================================================================
    template <typename T>
    void limitRange(T& value, T low, T high)
    {
        assert(low <= high);
        if (value < low)
        {
            value = low;
        }
        else if (value > high)
        {
            value = high;
        }
    }
    
    //==============================================================================
    template <typename T>
    T limitedRange(T value, T low, T high)
    {
        assert(low <= high);
        if (value < low)
        {
            return low;
        }
        else if (value > high)
        {
            return high;
        }
        return value;
    }
    
    //==============================================================================
    template <typename T>
    bool inRange(T value, T low, T high)
    {
        assert(low <= high);
        return value >= low && value <= high;
    }
    
    //==============================================================================
    inline int nextPowerOf2(int n)
    {
        --n;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
    }
    
    //==============================================================================
    inline int fftOrderFor(int pNumSamples)
    {
        int v = nextPowerOf2(pNumSamples);  // find the number of trailing zeros in 32-bit v
        constexpr const int MultiplyDeBruijnBitPosition[32] =
        {
            0, 1, 28, 2, 29, 14, 24, 3, 30, 22, 20, 15, 25, 17, 4, 8,
            31, 27, 13, 23, 21, 19, 16, 7, 26, 12, 18, 6, 11, 5, 10, 9
        };
        return MultiplyDeBruijnBitPosition[((uint32_t)((v/* & -v*/) * 0x077CB531U)) >> 27];
    }
    
    //==============================================================================
    inline bool isPowerOf2(unsigned int x)
    {
        return ((x != 0) && ((x & (~x + 1)) == x));
    }
    
    //==============================================================================
    template<typename T>
    T dBToGain(T pDB)
    {
        return std::pow((T)10, pDB / (T)20);
    }
    
    //==============================================================================
    template <typename T>
    T affineTransform(T fromMin, T fromMax, T toMin, T toMax, T value)
    {
        T fromMaxMinusFromMin = fromMax - fromMin;
        assert(fromMaxMinusFromMin != (T)0);
        return toMin + (toMax - toMin)*(value - fromMin)/fromMaxMinusFromMin;
    }
    
    //==============================================================================
    template<typename T>
    T square(T pVal)
    {
        return pVal * pVal;
    }
}

#endif
