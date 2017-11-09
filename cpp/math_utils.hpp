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

#include <cstdint>
#include <cassert>
#include <algorithm>

#define DEG2RAD (M_PI / 180.)
#define DEG2RADf (M_PIf / 180.f)
#define RAD2DEG (180. / M_PI)
#define RAD2DEGf (180.f / M_PIf)

#if _MSC_VER
#ifdef __LITTLE_ENDIAN__
static_assert(false)
#endif // __LITTLE_ENDIAN__
#define __LITTLE_ENDIAN__   1   //  Windows is always little-endian
#endif

namespace mu
{
    //==============================================================================
    template <typename T>
    T finvsqrt(T x)
    {
        //assert(x >= (T)0); // caller is responsible for checking that
        return (T)1 / std::sqrt(x); // the compiler is expected to detect and optimize this,
                                    // but /!\ that may not actually happen 
    }
    
#if 0
    /**
     @copyright public domain
     */
    template <>
    inline float finvsqrt<float>(float number)
    {
        float x2 = number * 0.5f;
        float y = number;
        uint32_t i = *(uint32_t*)&y;
        i = 0x5f375a86 - (i >> 1);
        y = *(float*) &i;
        y = y * (1.5f - (x2 * y * y));
        return y;
    }
    
    /**
     @copyright public domain
     */
    template <>
    inline double finvsqrt<double>(double number)
    {
        uint64_t i;
        double x2, y;
        x2 = number * 0.5;
        y = number;
        i = *(uint64_t*) &y;
        i = 0x5fe6eb50c7b537a9 - (i >> 1);
        y = *(double*) &i;
        y = y * (1.5 - (x2 * y * y));
        return y;
    }
#endif
    
    //==============================================================================
    /**
     Check if an angle is in )-π,π)
     */
    inline bool isDomainAngle(float pAngle)
    {
        return ((pAngle > - M_PIf) && (pAngle <= M_PIf));
    }
    
    //==============================================================================
    /**
     Check if an angle is in (-π,π)
     */
    inline bool isDomainAnglePermissive(float pAngle)
    {
        return ((pAngle >= - M_PIf) && (pAngle <= M_PIf));
    }
    
    //==============================================================================
    /**
     Get an angle in )-π,π) provided the input is in )-3π,3π)
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
    /**
     Get an angle in )-π,π)
     */
    inline float domainAngle(float pAngle)
    {
        float lAngle = std::remainder(pAngle, 2.f * M_PIf);
        if (lAngle <= -M_PIf) // TODO: change the domain so as to avoid this
        {
            lAngle += 2.f * M_PIf;
        }
        assert(isDomainAngle(lAngle));
        return lAngle;
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
    constexpr bool inRange(T value, T low, T high)
    {
        //assert(low <= high);
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
    constexpr T dBToGain(T pDB)
    {
        return std::pow((T)10, pDB / (T)20);
    }
    
    //==============================================================================
    template <typename T>
    constexpr T affineTransform(T fromMin, T fromMax, T toMin, T toMax, T value)
    {
        //assert(fromMax - fromMin != (T)0);
        return toMin + (toMax - toMin) * (value - fromMin) / (fromMax - fromMin);
    }
    
    //==============================================================================
    template <typename T>
    constexpr T affineTransformLimited(T fromMin, T fromMax, T toMin, T toMax, T value)
    {
        return limitedRange(affineTransform(fromMin, fromMax, toMin, toMax, value), toMin, toMax);
    }
    
    //==============================================================================
    template<typename T>
    constexpr T square(T pVal)
    {
        return pVal * pVal;
    }
    
    //==============================================================================
    template<typename T>
    constexpr T cube(T pVal)
    {
        return pVal * pVal * pVal;
    }
    
    //==============================================================================
    /**
     @copyright public domain
     */
    inline float fast_log2(float val)
    {
        union {float f; int i;} t;
        t.f = val;
        int * const exp_ptr = &t.i;
        int x = *exp_ptr;
        const int log_2 = ((x >> 23) & 255) - 128;
        x &= ~(255 << 23);
        x += 127 << 23;
        *exp_ptr = x;
        
        val = ((-1.0f/3) * t.f + 2) * t.f - 2.0f/3;
        
        return (val + log_2);
    }
    
    /**
     @copyright public domain
     */
    inline float fast_log(const float val)
    {
        return (fast_log2(val) * 0.69314718f);
    }
    
    /**
     @copyright public domain
     */
    inline float fast_log10(const float val)
    {
        return fast_log2(val) / 3.312500f;
    }
    
    //==============================================================================
    inline float fast_gainToDB(const float g)
    {
        return 20.f * fast_log10(g);
    }
    
    inline float fast_powToDB(const float g)
    {
        return 10.f * fast_log10(g);
    }
    
    //==============================================================================
    /**
     @copyright public domain
     */
    inline int fastRoundToInt(double val)
    {
        union {double d; int i[2];} u;
        u.d = val + 6755399441055744.;
#ifdef __LITTLE_ENDIAN__
        return (int)u.i[0];
#else
        return (int)u.i[1];
#endif
    }
    
    //==============================================================================
    /**
     Valid on [-Pi, Pi] with an abs error inferior to 0.001
     */
    inline float fastSin7(float x)
    {
        float x2 = x * x;
        return x * (0.9992431032114582f + x2 * (- 0.16534994905656308f + x2 * (0.007873446865159112f - 0.00013964149131248947f * x2)));
    }
    
    /**
     Valid on [-Pi, Pi] with an abs error inferior to 0.00002
     */
    inline float fastSin9(float x)
    {
        float x2 = x * x;
        return x * (0.9999819223196827f + x2 * (-0.1666117333491961f + x2 * (0.008301994234527911f + x2 * (- 0.00019154801461966623f + 2.0943656646398535e-6f * x2))));
    }
    
    /**
     Valid on [-Pi, Pi] with an abs error inferior to 0.003
     */
    inline float fastCos6(float x)
    {
        float x2 = x * x;
        return 0.997357479120193f + x2 * (- 0.49360704701475366f + x2 * (0.03880981050760031f - 0.0009433852664416385f * x2));
    }
    
    /**
     Valid on [-Pi, Pi] with an abs error inferior to 0.0001
     */
    inline float fastCos8(float x)
    {
        float x2 = x * x;
        return 1.f + x2 * (- 0.49992234392040313f + x2 * (0.0415611407831821f + x2 * (- 0.0013497862134738713f + 0.00001932349100797763f * x2)));
    }
    
    /**
     Abs error inferior to 0.0063
     */
    inline float fast_asin4_3(float x)
    {
        if (x >= 0.f)
        {
            return x * (1.0086092643578328f + x * (1353.5141891115013f + x * (- 2433.7944299113137f + 1080.1972306769444f * x))) / (1.f + x * (1360.966200347148f + x * (- 2532.1768321940885f + 1170.8022308154443f * x)));
        }
        else
        {
            return -fast_asin4_3(-x);
        }
    }
    
    //==============================================================================
    /**
     Branchless max
     @copyright public domain
     */
    inline int32_t imax(int32_t a, int32_t b)
    {
        // signed for arithmetic shift
        int32_t mask = a - b;
        // mask < 0 means MSB is 1.
        return a + ( ( b - a ) & ( mask >> 31 ) );
    }
    
    //==============================================================================
    template <typename T>
    T minOverMax(T a, T b)
    {
        if (a < b)
        {
            return a / b;
        }
        else
        {
            return b / a;
        }
    }
    
    //==============================================================================
    /**
     Saturating arithmetics
     */
    inline uint8_t saturating_add(uint8_t pA, uint8_t pB)
    {
#if 1 // actually faster
        int16_t lResult = (int16_t)pA + (int16_t)pB;
        if (lResult > 255)
            return 255;
        else
            return lResult;
#else
        uint16_t lResultMod = ((uint16_t)pA + (uint16_t)pB);
        bool lCarry = lResultMod & 256;
        return (lCarry * 255) | (!lCarry * lResultMod);
#endif
    }
    
    inline uint8_t saturating_subtract(uint8_t pA, uint8_t pB)
    {
#if 1 // actually faster
        int16_t lResult = (int16_t)pA - (int16_t)pB;
        if (lResult < 0)
            return 0;
        else
            return lResult;
#else
        uint16_t lResultMod = ((uint16_t)pA - (uint16_t)pB);
        bool lCarry = lResultMod & 32768;
        return !lCarry * lResultMod;
#endif
    }
    
    //=============================================================================
    /**
     Sum of two decibel values
     */
    inline uint8_t fast_dBSum0_2(uint8_t pA, uint8_t pB)
    {
        float lDiff = std::abs((float)pA - (float)pB);
        float lDelta = 54.8697f / (19.2149f + lDiff * (0.686395f + lDiff));
        return std::max(pA, pB) + mu::fastRoundToInt(lDelta);
    }
    
    inline uint8_t fast_dBSum0_5(uint8_t pA, uint8_t pB)
    {
        float lDiff = std::abs((float)pA - (float)pB);
        float lDelta = 3.01055f / (1.f + lDiff * (0.166853f + lDiff * (0.0170169f + lDiff * (0.00188077f + lDiff * (- 0.000011882f + 0.0000114037f * lDiff)))));
        return std::max(pA, pB) + mu::fastRoundToInt(lDelta);
    }
    
    inline uint8_t approx_dBSum(uint8_t pA, uint8_t pB)
    {
        // simplified as the max of both values, sufficient in many cases
        return std::max(pA, pB); // use branchless max if more efficient
    }
    
    //==============================================================================
    template <typename T>
    void boundsSafeGuard(T* pChannel, int pNumSamples)
    {
        for (int i = 0 ; i != pNumSamples ; ++i)
        {
            if (! std::isfinite(pChannel[i]))
            {
                pChannel[i] = (T)0;
            }
        }
    }
    
    //==============================================================================
    template <typename T>
    void manualFTZ(T* pChannel, int pNumSamples)
    {
        for (int i = 0 ; i != pNumSamples ; ++i)
        {
            if (! std::isnormal(pChannel[i]))
            {
                pChannel[i] = (T)0;
            }
        }
    }
}

#endif
