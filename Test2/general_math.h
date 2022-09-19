#pragma once

#include <cmath>
#include <math.h>
#include <iostream>

class Math {
public:
    static const float PI;
    static const float PI_HALVES;
    static const float PI_THIRDS;
    static const float PI_FOURTHS;
    static const float PI_SIXTHS;
    static const float PI_2;
    static const float PI_INVx180;
    static const float PI_DIV180;
    static const float PI_INV;
    static const float ZERO;

    Math();

    inline static bool  isZero(float fValue);
    inline static float sign(float fValue);

    inline static int   randomRange(int iMin, int iMax);
    inline static float randomRange(float fMin, float fMax);

    inline static float degree2Radian(float fDegrees);
    inline static float radian2Degree(float fRadians);
    inline static float correctAngle(float fAngle, bool bDegrees, float fAngleStart = 0.0f);
    inline static float mapValue(float fMinY, float fMaxY, float fMinX, float fMaxX, float fValueX);

    template<class T>
    inline static void constrain(T min, T max, T& value);

    template<class T>
    inline static void swap(T& value1, T& value2);

}; // Math

// -----------------------------------------------------------------------
// degree2Radian()
// Convert Angle In Degrees To Radians
inline float Math::degree2Radian(float fDegrees) 
{
    return fDegrees * PI_DIV180;
}

// -----------------------------------------------------------------------
// radian2Degree()
// Convert Angle In Radians To Degrees
inline float Math::radian2Degree(float fRadians) 
{
    return fRadians * PI_INVx180;
}

// -----------------------------------------------------------------------
// correctAngle()
// Returns An Angle Value That Is Alway Between fAngleStart And fAngleStart + 360
// If Radians Are Used, Then Range Is fAngleStart To fAngleStart + 2PI
inline float Math::correctAngle(float fAngle, bool bDegrees, float fAngleStart) 
{
    if (bDegrees) 
    {
        // Using Degrees
        if (fAngle < fAngleStart) 
        {
            while (fAngle < fAngleStart) 
            {
                fAngle += 360.0f;
            }
        }
        else if (fAngle >= (fAngleStart + 360.0f)) 
        {
            while (fAngle >= (fAngleStart + 360.0f)) 
            {
                fAngle -= 360.0f;
            }
        }
        return fAngle;
    }
    else 
    {
        // Using Radians
        if (fAngle < fAngleStart) 
        {
            while (fAngle < fAngleStart) 
            {
                fAngle += Math::PI_2;
            }
        }
        else if (fAngle >= (fAngleStart + Math::PI_2)) 
        {
            while (fAngle >= (fAngleStart + Math::PI_2)) 
            {
                fAngle -= Math::PI_2;
            }
        }

        return fAngle;
    }
}

// -----------------------------------------------------------------------
// isZero()
// Tests If Input Value Is Close To Zero
inline bool Math::isZero(float fValue) 
{
    if ((fValue > -ZERO) && (fValue < ZERO)) 
    {
        return true;
    }
    return false;
}

// -----------------------------------------------------------------------
// sign()
// Returns 1 If Value Is Positive, -1 If Value Is Negative Or 0 Otherwise
inline float Math::sign(float fValue) 
{
    if (fValue > 0) 
    {
        return 1.0f;
    }
    else if (fValue < 0) 
    {
        return -1.0f;
    }
    return 0;
}

// -----------------------------------------------------------------------
// randomRange()
// Return A Random Number Between iMin And iMax Where iMin < iMax
inline int Math::randomRange(int iMin, int iMax) 
{
    if (iMax < iMin) 
    {
        swap(iMax, iMin);
    }
    return (iMin + ((iMax - iMin + 1) * rand()) / (RAND_MAX + 1));
}

// -----------------------------------------------------------------------
// randomRange()
// Return A Random Number Between fMin And fMax Where fMin < fMax
inline float Math::randomRange(float fMin, float fMax) 
{
    if (fMax < fMin) {
        swap(fMax, fMin);
    }
    return (fMin + (rand() / (float)RAND_MAX) * (fMax - fMin));
}

// -----------------------------------------------------------------------
// mapValue()
// Returns The fValueY That Corresponds To A Point On The Line Going From Min To Max
inline float Math::mapValue(float fMinY, float fMaxY, float fMinX, float fMaxX, float fValueX) 
{
    if (fValueX >= fMaxX) 
    {
        return fMaxY;
    }
    else if (fValueX <= fMinX) 
    {
        return fMinY;
    }
    else 
    {
        float fM = (fMaxY - fMinY) / (fMaxX - fMinX);
        float fB = fMaxY - fM * fMaxX;
        return (fM * fValueX + fB);
    }
}

// -----------------------------------------------------------------------
// constrain()
// Prevent Value From Going Outside The Min, Max Range.
template<class T>
inline void Math::constrain(T min, T max, T& value) 
{
    if (value < min) 
    {
        value = min;
        return;
    }

    if (value > max) 
    {
        value = max;
    }
}

// -----------------------------------------------------------------------
// swap()
//
template<class T>
inline void Math::swap(T& value1, T& value2) 
{
    T temp;
    temp = value1;
    value1 = value2;
    value2 = temp;
}
