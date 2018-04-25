#ifndef FBU_VECTOR3_HPP_INCLUDED
#define FBU_VECTOR3_HPP_INCLUDED

/**
 @file vector3.hpp
 @author François Becker

MIT License

Copyright (c) 2016-2018 François Becker

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

template <typename T> struct AE;
template <typename T> struct AEM;
template <typename T> struct AEMr;
template <typename T> struct Vector3;

//==============================================================================
/**
 @brief A POD 3-dimensional space vector.
 */
template <typename T>
struct Vector3
{
    T mX;
    T mY;
    T mZ;
    
    static Vector3<T> cartesian(T pX, T pY, T pZ)
    {
        Vector3<T> lResult;
        lResult.mX = pX;
        lResult.mY = pY;
        lResult.mZ = pZ;
        return lResult;
    }
    static Vector3<T> fromAE(const AE<T>& pAE);
    static Vector3<T> fromAEM(const AEM<T>& pAEM);
    static Vector3<T> fromAEMr(const AEMr<T>& pAEM);
    
    bool isZero() const
    {
        return mX == (T)0.f && mY == (T)0.f && mZ == (T)0.f;
    }
    
    T dot(const Vector3<T>& pOther) const
    {
        T lResult;
        lResult = mX * pOther.mX;
        lResult += mY * pOther.mY;
        lResult += mZ * pOther.mZ;
        return lResult;
    }
    
    Vector3<T> cross(const Vector3<T>& pOther) const
    {
        return {
            mY * pOther.mZ - mZ * pOther.mY,
            mZ * pOther.mX - mX * pOther.mZ,
            mX * pOther.mY - mY * pOther.mX
        };
    }
    
    T length() const
    {
        return std::sqrt(mX * mX + mY * mY + mZ * mZ);
        // or? return std::hypot(mZ, std::hypot(mX, mY));
    }
    
    T sqrLength() const
    {
        return mX * mX + mY * mY + mZ * mZ;
    }
    
    void lengthes(T& pLength3D, T& pLength2D) const
    {
        pLength2D = std::hypot(mX, mY);
        pLength3D = std::hypot(pLength2D, mZ);
    }
    
    void normalize()
    {
        T lSqrLength = sqrLength();
        assert(lSqrLength != (T)0);
        T lInvLength = mu::finvsqrt(lSqrLength);
        mX *= lInvLength;
        mY *= lInvLength;
        mZ *= lInvLength;
    }
    
    void normalizeWithDefault(const Vector3<T>& pDefault)
    {
        T lSqrLength = sqrLength();
        if (lSqrLength != (T)0)
        {
            T lInvLength = mu::finvsqrt(lSqrLength);
            mX *= lInvLength;
            mY *= lInvLength;
            mZ *= lInvLength;
        }
        else
        {
            mX = pDefault.mX;
            mY = pDefault.mY;
            mZ = pDefault.mZ;
        }
    }
    
    Vector3<T> normalized() const
    {
        Vector3<T> lVect(*this);
        lVect.normalize();
        return lVect;
    }
    
    Vector3<T> normalizedWithDefault(const Vector3<T>& pDefault) const
    {
        Vector3<T> lVect(*this);
        lVect.normalizeWithDefault(pDefault);
        return lVect;
    }
};

template <typename T>
Vector3<T> operator +(const Vector3<T>& pA, const Vector3<T>& pB)
{
    Vector3<T> lResult;
    lResult.mX = pA.mX + pB.mX;
    lResult.mY = pA.mY + pB.mY;
    lResult.mZ = pA.mZ + pB.mZ;
    return lResult;
}

template <typename T>
Vector3<T> operator -(const Vector3<T>& pA, const Vector3<T>& pB)
{
    Vector3<T> lResult;
    lResult.mX = pA.mX - pB.mX;
    lResult.mY = pA.mY - pB.mY;
    lResult.mZ = pA.mZ - pB.mZ;
    return lResult;
}

template <typename T>
Vector3<T> operator *(T pS, const Vector3<T>& pV)
{
    Vector3<T> lResult;
    lResult.mX = pS * pV.mX;
    lResult.mY = pS * pV.mY;
    lResult.mZ = pS * pV.mZ;
    return lResult;
}

template <typename T>
Vector3<T> operator *=(Vector3<T>& pV, T pS)
{
    pV.mX *= pS;
    pV.mY *= pS;
    pV.mZ *= pS;
    return pV;
}

template <typename T>
Vector3<T> operator +=(Vector3<T>& pV, const Vector3<T>& pA)
{
    pV.mX += pA.mX;
    pV.mY += pA.mY;
    pV.mZ += pA.mZ;
    return pV;
}

template <typename T>
bool operator <(const Vector3<T>& pA, const Vector3<T>& pB)
{
    if (pA.mX < pB.mX)
    {
        return true;
    }
    else if (pA.mX == pB.mX)
    {
        if (pA.mY < pB.mY)
        {
            return true;
        }
        else if (pA.mY == pB.mY)
        {
            if (pA.mZ < pB.mZ)
            {
                return true;
            }
        }
    }
    return false;
}

typedef Vector3<float> Vector3f;

template <typename T> struct AEM;

//==============================================================================
/**
 @brief  A POD struct for Azimuth, Elevation
 */
template <typename T>
struct AE
{
    static AE<T> ae(T pAzimuth, T pElevation = (T) 0.f)
    {
        AE<T> lResult;
        lResult.mAzimuth = pAzimuth;
        lResult.mElevation = pElevation;
        return lResult;
    }
    
    static AE<T> fromNormalizedVector3(const Vector3<T>& pVect)
    {
        AE lAE;
        lAE.mAzimuth = std::atan2(pVect.mY, pVect.mX);
        assert(mu::inRange(pVect.mZ, (T)(-1), (T)1));
#ifdef __EMSCRIPTEN__
        lAE.mElevation = mu::fast_asin4_3(pVect.mZ);
#else
        lAE.mElevation = std::asin(pVect.mZ);
#endif
        return lAE;
    }
    
    static AE<T> fromAEM(const AEM<T>& pAEM)
    {
        return {pAEM.mAzimuth, pAEM.mElevation};
    }
    
    T mAzimuth;
    T mElevation;
};

typedef AE<float> AEf;

//==============================================================================
/**
 @brief  A POD struct for Azimuth, Elevation, Magnitude
 */
template <typename T>
struct AEM
{
    static AEM<T> aem(T pAzimuth, T pElevation = (T)0.f, T pMagnitude = (T)1.f)
    {
        AEM<T> lResult;
        lResult.mAzimuth = pAzimuth;
        lResult.mElevation = pElevation;
        lResult.mMagnitude = pMagnitude;
        return lResult;
    }
    
    static AEM<T> fromVector3(const Vector3<T>& pVect)
    {
        AEM lAEM;
        float lNorm2D;
        pVect.lengthes(lAEM.mMagnitude, lNorm2D);
        lAEM.mAzimuth = std::atan2(pVect.mY, pVect.mX);
        lAEM.mElevation = std::atan2(pVect.mZ, lNorm2D);
        return lAEM;
    }
    
    static AEM<T> fromNormalizedVector3(const Vector3<T>& pVect)
    {
        AEM lAEM;
        lAEM.mAzimuth = std::atan2(pVect.mY, pVect.mX);
        assert(mu::inRange(pVect.mZ, (T)(-1), (T)1));
#ifdef __EMSCRIPTEN__
        lAEM.mElevation = mu::fast_asin4_3(pVect.mZ);
#else
        lAEM.mElevation = std::asin(pVect.mZ);
#endif
        return lAEM;
    }
    
    AEM<T> withMagnitude(T pMagnitude) const
    {
        AEM lAEM(*this);
        lAEM.mMagnitude = pMagnitude;
        return lAEM;
    }
    
    T mAzimuth;     ///< rad, 0 in front, positive to the left
    T mElevation;   ///< rad, 0 in front, positive to the top
    T mMagnitude;
};

template <typename T>
AEM<T> operator *(T pS, const AEM<T>& pAEM)
{
    AEM<T> lResult;
    lResult.mAzimuth = pAEM.mAzimuth;
    lResult.mElevation = pAEM.mElevation;
    lResult.mMagnitude = pS * pAEM.mMagnitude;
    return lResult;
}

typedef AEM<float> AEMf;
template AEM<float> AEM<float>::fromVector3(const Vector3<float> &pVect);
template AEM<float> AEM<float>::fromNormalizedVector3(const Vector3<float> &pVect);

//==============================================================================
/**
 @brief  Azimuth, Elevation, Magnitude, with azimuth reversed
 */
template <typename T>
struct AEMr
{
    AEMr()
    : mAzimuth(0)
    , mElevation(0)
    , mMagnitude(0)
    {
    }
    
    AEMr(T pAzimuth, T pElevation, T pMagnitude)
    : mAzimuth(pAzimuth)
    , mElevation(pElevation)
    , mMagnitude(pMagnitude)
    {
    }
    
    T mAzimuth;     ///< rad, 0 in front, positive to the right
    T mElevation;   ///< rad, 0 in front, positive to the top
    T mMagnitude;
};

typedef AEMr<float> AEMrf;

//==============================================================================
template <typename T>
void Vector3_to_AEMr(const Vector3<T>& pVect, AEMr<T>& pAEM)
{
    pAEM.mAzimuth = 0.f;
    pAEM.mElevation = 0.f;
    float lMagnitude2D = std::hypot(pVect.mX, pVect.mY);
    pAEM.mMagnitude = std::hypot(lMagnitude2D, pVect.mZ);
    if (pAEM.mMagnitude != 0.f)
    {
        T lSinElevation = pVect.mZ / pAEM.mMagnitude;
        assert(inRange(lSinElevation, (T)(-1), (T)1));
#ifdef __EMSCRIPTEN__
        pAEM.mElevation = mu::fast_asin4_3(lSinElevation);
#else
        pAEM.mElevation = std::asin(lSinElevation);
#endif
        if (std::abs(pAEM.mElevation) <= M_PI_2f - (0.5f * DEG2RADf))
        {
            T lCosAzimuth = pVect.mX / lMagnitude2D;
            assert(inRange(lCosAzimuth, (T)(-1), (T)1));
            pAEM.mAzimuth = std::acos(lCosAzimuth);
            if (pVect.mY > 0.f)
            {
                pAEM.mAzimuth = -pAEM.mAzimuth;
            }
        }
    }
}

//==============================================================================
template <typename T>
Vector3<T> Vector3<T>::fromAEMr(const AEMr<T>& pAEM)
{
    Vector3<T> lVect;
    float lCosAzimuth = std::cos(pAEM.mAzimuth);
    float lSinAzimuth = std::sin(pAEM.mAzimuth);
    float lCosElevation = std::cos(pAEM.mElevation);
    float lSinElevation = std::sin(pAEM.mElevation);
    lVect.mX = pAEM.mMagnitude * lCosElevation * lCosAzimuth;
    lVect.mY = - pAEM.mMagnitude * lCosElevation * lSinAzimuth;
    lVect.mZ = pAEM.mMagnitude * lSinElevation;
    return lVect;
}

//==============================================================================
template <typename T>
Vector3<T> Vector3<T>::fromAEM(const AEM<T>& pAEM)
{
    Vector3<T> lVect;
#ifdef __EMSCRIPTEN__
    float lCosAzimuth = mu::fastCos8(pAEM.mAzimuth);
    float lSinAzimuth = mu::fastSin9(pAEM.mAzimuth);
    float lCosElevation = mu::fastCos8(pAEM.mElevation);
    float lSinElevation = mu::fastSin9(pAEM.mElevation);
#else
    float lCosAzimuth = std::cos(pAEM.mAzimuth);
    float lSinAzimuth = std::sin(pAEM.mAzimuth);
    float lCosElevation = std::cos(pAEM.mElevation);
    float lSinElevation = std::sin(pAEM.mElevation);
#endif
    lVect.mX = pAEM.mMagnitude * lCosElevation * lCosAzimuth;
    lVect.mY = pAEM.mMagnitude * lCosElevation * lSinAzimuth;
    lVect.mZ = pAEM.mMagnitude * lSinElevation;
    return lVect;
}

//==============================================================================
template <typename T>
Vector3<T> Vector3<T>::fromAE(const AE<T>& pAE)
{
    Vector3<T> lVect;
#ifdef __EMSCRIPTEN__
    float lCosAzimuth = mu::fastCos8(pAE.mAzimuth);
    float lSinAzimuth = mu::fastSin9(pAE.mAzimuth);
    float lCosElevation = mu::fastCos8(pAE.mElevation);
    float lSinElevation = mu::fastSin9(pAE.mElevation);
#else
    float lCosAzimuth = std::cos(pAE.mAzimuth);
    float lSinAzimuth = std::sin(pAE.mAzimuth);
    float lCosElevation = std::cos(pAE.mElevation);
    float lSinElevation = std::sin(pAE.mElevation);
#endif
    lVect.mX = lCosElevation * lCosAzimuth;
    lVect.mY = lCosElevation * lSinAzimuth;
    lVect.mZ = lSinElevation;
    return lVect;
}

#endif
