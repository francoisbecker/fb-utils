#ifndef FBU_VECTOR2_HPP_INCLUDED
#define FBU_VECTOR2_HPP_INCLUDED

/**
 @file vector2.hpp
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

#include "fbu/math_float_constants.hpp"
#include "fbu/math_utils.hpp"

#include <cmath>
#include <cassert>

//==============================================================================
template <typename T>
struct Vector2
{
    T mX;
    T mY;
    
    Vector2<T>()
    {
    }
    
    Vector2<T>(T pX, T pY)
    : mX(pX)
    , mY(pY)
    {
    }
    
    T dot(const Vector2<T>& pOther) const
    {
        T lResult;
        lResult = mX * pOther.mX;
        lResult += mY * pOther.mY;
        return lResult;
    }
    
    T length() const
    {
        return std::hypot(mX, mY);
    }
    
    T sqrLength() const
    {
        return mX * mX + mY * mY;
    }
    
    void normalize()
    {
        T lSqrLength = sqrLength();
        assert(lSqrLength != (T)0);
        T lInvLength = mu::finvsqrt(lSqrLength);
        mX *= lInvLength;
        mY *= lInvLength;
    }
    
    Vector2<T> normalized() const
    {
        Vector2<T> lVect(*this);
        lVect.normalize();
        return lVect;
    }
    
    Vector2<T> orthogonalPos() const
    {
        return Vector2<T>(-this->mY, this->mX);
    }
    
    Vector2<T> orthogonalNeg() const
    {
        return Vector2<T>(this->mY, -this->mX);
    }
    
    Vector2<T> rotated(T pAngle) const
    {
#ifdef __EMSCRIPTEN__
        T lSinAngle = mu::fastSin9(pAngle);
        T lCosAngle = mu::fastCos8(pAngle);
#else
        T lSinAngle = std::sin(pAngle);
        T lCosAngle = std::cos(pAngle);
#endif
        return Vector2<T>(lCosAngle * this->mX - lSinAngle * this->mY,
                          lSinAngle * this->mX + lCosAngle * this->mY);
    }
    
    static T unsigned_angle(const Vector2<T>& pA, const Vector2<T>& pB)
    {
        return (pA.dot(pB)) / (pA.length() * pB.length());
    }
    
    static T angle_sign(const Vector2<T>& pA, const Vector2<T>& pB)
    {
        return std::copysign((T)1, pA.orthogonalPos().dot(pB));
    }
    
    static T signed_angle(const Vector2<T>& pA, const Vector2<T>& pB)
    {
        return angle_sign(pA, pB) * unsigned_angle(pA, pB);
    }
};

template <typename T>
Vector2<T> operator +(const Vector2<T>& pA, const Vector2<T>& pB)
{
    Vector2<T> lResult;
    lResult.mX = pA.mX + pB.mX;
    lResult.mY = pA.mY + pB.mY;
    return lResult;
}

template <typename T>
Vector2<T> operator -(const Vector2<T>& pA, const Vector2<T>& pB)
{
    Vector2<T> lResult;
    lResult.mX = pA.mX - pB.mX;
    lResult.mY = pA.mY - pB.mY;
    return lResult;
}

template <typename T>
Vector2<T> operator *(T pS, const Vector2<T>& pV)
{
    Vector2<T> lResult;
    lResult.mX = pS * pV.mX;
    lResult.mY = pS * pV.mY;
    return lResult;
}

template <typename T>
Vector2<T> operator *=(Vector2<T>& pV, T pS)
{
    pV.mX *= pS;
    pV.mY *= pS;
    return pV;
}

typedef Vector2<float> Vector2f;

#endif
