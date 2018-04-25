#ifndef FBU_COMPLEX_HPP_INCLUDED
#define FBU_COMPLEX_HPP_INCLUDED

/**
 @file complex.hpp
 @author François Becker

MIT License

Copyright (c) 2016-2017 François Becker

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

#include "fbu/math_utils.hpp"

#include <cmath>

template<typename T>
struct Complex
{
    T re;
    T im;
    
    Complex<T> conj() const
    {
        return Complex<T>({re, -im});
    }
    
    T mag() const
    {
        return std::hypot(re, im);
    }
    
    T sqrmag() const
    {
        return re * re + im * im;
    }
    
    T arg() const
    {
        return std::atan2(im, re);
    }
    
    static Complex<T> polar(const T mag, const T arg)
    {
        return Complex<T>({mag * std::cos(arg),
                           mag * std::sin(arg)});
    }
    
    static Complex<T> fastPolar(const T mag, const T arg)
    {
        T domainarg = mu::domainAngle(arg);
        return Complex<T>({mag * mu::fastCos8(domainarg),
                           mag * mu::fastSin9(domainarg)});
    }
    
    Complex<T> inverse() const
    {
        return conj() / sqrmag();
    }
    
    T dot(Complex<T> a) const
    {
        return re * a.re + im * a.im;
    }
    
    static Complex<T> hypot(Complex<T> pFirst, Complex<T> pSecond)
    {
        // TODO: validate mathematically
        Complex<T> lFirstWithSqr = pFirst * pFirst.mag();
        Complex<T> lSecondWithSqr = pSecond * pSecond.mag();
        Complex<T> lSqrSum = lFirstWithSqr + lSecondWithSqr;
        T lSqrSumMag = lSqrSum.mag();
        if (lSqrSumMag != (T)0)
        {
            return ((T)1 / std::sqrt(lSqrSumMag)) * lSqrSum;
        }
        else
        {
            return {(T)0, (T)0};
        }
    }
    
    Complex<T>& operator+=(const Complex<T>& a)
    {
        re += a.re;
        im += a.im;
        return *this;
    }
    
    Complex<T>& operator-=(const Complex<T>& a)
    {
        re -= a.re;
        im -= a.im;
        return *this;
    }
    
    Complex<T>& operator*=(const T& s)
    {
        re *= s;
        im *= s;
        return *this;
    }
    
    Complex<T>& operator*=(const Complex<T>& a)
    {
        *this = *this * a;
        return *this;
    }
    
    Complex<T>& operator/=(const T& s)
    {
        float sinv = ((T)1) / s;
        re *= sinv;
        im *= sinv;
        return *this;
    }
    
    Complex<T>& operator/=(const Complex<T>& a)
    {
        Complex<T> ainv = a.inverse();
        *this = *this * ainv;
        *this = *this * ainv;
        return *this;
    }
    
    template <typename R>
    Complex<T>& operator=(const R& r)
    {
        re = (T)r;
        im = (T)0;
        return *this;
    }
};

template<typename T>
Complex<T> operator+(const Complex<T> a, const Complex<T> b)
{
    return Complex<T>({a.re + b.re, a.im + b.im});
}

template<typename T>
Complex<T> operator-(const Complex<T> a, const Complex<T> b)
{
    return Complex<T>({a.re - b.re, a.im - b.im});
}

template<typename T>
Complex<T> operator*(const Complex<T> a, const Complex<T> b)
{
    return Complex<T>({a.re * b.re - a.im * b.im,
                       a.im * b.re + a.re * b.im});
}

template<typename T>
Complex<T> operator*(const T s, const Complex<T> a)
{
    return Complex<T>({s * a.re, s * a.im});
}

template<typename T>
Complex<T> operator*(const Complex<T> a, const T s)
{
    return Complex<T>({s * a.re, s * a.im});
}

template<typename T>
Complex<T> operator/(const Complex<T> a, const Complex<T> b)
{
    return (((T)1)/b.sqrmag()) * Complex<T>({a.re * b.re + a.im * b.im,
                                             a.im * b.re - a.re * b.im});
}

template<typename T>
Complex<T> operator/(const Complex<T> a, const T s)
{
    return (((T)1)/s) * a;
}

template<typename T>
bool operator==(const Complex<T> a, const Complex<T> b)
{
    return a.re == b.re && a.im == b.im;
}

template<typename T>
bool operator!=(const Complex<T> a, const Complex<T> b)
{
    return a.re != b.re || a.im != b.im;
}

//==============================================================================
template<typename T>
void vectSymConj(Complex<T>* pV, size_t pSize)
{
    // Symmetric conjugate
    for (size_t u = 1 ; u != pSize / 2 ; ++u)
    {
        pV[pSize - u] = pV[u].conj();
    }
}

template<typename T>
void vectSubtract_I(const Complex<T>* __restrict pIn, Complex<T>* __restrict pInOut, size_t pSize)
{
    for (size_t u = 0 ; u != pSize ; ++u)
    {
        pInOut[u] -= pIn[u];
    }
}

template<typename T>
void vectProductSC_I(T pS, Complex<T>* pInOut, size_t pSize)
{
    for (size_t u = 0 ; u != pSize ; ++u)
    {
        pInOut[u] *= pS;
    }
}

//==============================================================================
typedef Complex<float> Complexf;
typedef Complex<double> Complexd;

#endif
