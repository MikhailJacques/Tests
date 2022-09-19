#pragma once

#include "general_math.h"

class Vector3D {

public:
    union {
        float m_f3[3];
        struct {
            float m_fX;
            float m_fY;
            float m_fZ;
        };
    };

    inline Vector3D();
    inline Vector3D(float x, float y, float z);
    inline Vector3D(float* pfv);
    ~Vector3D() {}

    // Operators
    inline Vector3D  operator+(const Vector3D& v3) const;
    inline Vector3D  operator+() const;
    inline Vector3D& operator+=(const Vector3D& v3);
    inline Vector3D  operator-(const Vector3D& v3) const;
    inline Vector3D  operator-() const;
    inline Vector3D& operator-=(const Vector3D& v3);
    inline Vector3D  operator*(const float& fValue) const;
    inline Vector3D& operator*=(const float& fValue);
    inline Vector3D  operator/(const float& fValue) const;
    inline Vector3D& operator/=(const float& fValue);

    // operator*() - pre-multiply vector by a scalar
    inline friend Vector3D operator*(const float& fValue, const Vector3D v3)
    {
        return Vector3D(fValue * v3.m_fX, fValue * v3.m_fY, fValue * v3.m_fZ);

    }

    // operator/() - pre-divide vector by a scalar value
    inline friend Vector3D operator/(const float& fValue, const Vector3D v3)
    {
        Vector3D vec3;

        if (Math::isZero(v3.m_fX)) 
        {
            vec3.m_fX = 0.0f;
        }
        else 
        {
            vec3.m_fX = fValue / v3.m_fX;
        }

        if (Math::isZero(v3.m_fY)) 
        {
            vec3.m_fY = 0.0f;
        }
        else 
        {
            vec3.m_fY = fValue / v3.m_fY;
        }

        if (Math::isZero(v3.m_fZ)) 
        {
            vec3.m_fZ = 0.0f;
        }
        else 
        {
            vec3.m_fZ = fValue / v3.m_fZ;
        }

        return vec3;
    }

    // Functions    
    inline Vector3D rotateX(float fRadians);
    inline Vector3D rotateY(float fRadians);
    inline Vector3D rotateZ(float fRadians);

    inline void setPerpendicularXZ(Vector3D v3);
    inline void setPerpendicularXY(Vector3D v3);
    inline void setPerpendicularYZ(Vector3D v3);

    inline Vector3D cross(const Vector3D v3) const;
    inline float dot(const Vector3D v3) const;
    inline float getAngle(const Vector3D& v3, const bool bNormalized = false, bool bRadians = true);
    inline float getCosAngle(const Vector3D& v3, const bool bNormalized = false);
    inline float length() const;
    inline float length2() const;
    inline void normalize();
    inline void zero();
    inline bool isZero() const;

};

// Constructor
inline Vector3D::Vector3D()
{
    m_fX = 0.0f;
    m_fY = 0.0f;
    m_fZ = 0.0f;
}

// Constructor
inline Vector3D::Vector3D(float x, float y, float z)
{
    m_fX = x;
    m_fY = y;
    m_fZ = z;
}

// Constructor
inline Vector3D::Vector3D(float* pfv)
{
    m_fX = pfv[0];
    m_fY = pfv[1];
    m_fZ = pfv[2];
}

// Unary operator+()
inline Vector3D Vector3D::operator+() const
{
    return *this;
}

// Binary operator+() - add two vectors together
inline Vector3D Vector3D::operator+(const Vector3D& v3) const
{
    return Vector3D(m_fX + v3.m_fX, m_fY + v3.m_fY, m_fZ + v3.m_fZ);
}

// operator+=() - add two vectors together
inline Vector3D& Vector3D::operator+=(const Vector3D& v3)
{
    m_fX += v3.m_fX;
    m_fY += v3.m_fY;
    m_fZ += v3.m_fZ;

    return *this;
}

// Unary operator-() - negate each value
inline Vector3D Vector3D::operator-() const
{
    return Vector3D(-m_fX, -m_fY, -m_fZ);
}

// Binary operator-() - Take this vector and subtract another vector from it
inline Vector3D Vector3D::operator-(const Vector3D& v3) const
{
    return Vector3D(m_fX - v3.m_fX, m_fY - v3.m_fY, m_fZ - v3.m_fZ);
}

// operator-=() - Subtract two vectors from each other
inline Vector3D& Vector3D::operator-=(const Vector3D& v3)
{
    m_fX -= v3.m_fX;
    m_fY -= v3.m_fY;
    m_fZ -= v3.m_fZ;

    return *this;
}

// operator*() - post-multiply vector by a scalar 
inline Vector3D Vector3D::operator*(const float& fValue) const
{
    return Vector3D(m_fX * fValue, m_fY * fValue, m_fZ * fValue);
}

// operator*=() - multiply this vector by A scalar
inline Vector3D& Vector3D::operator*=(const float& fValue)
{
    m_fX *= fValue;
    m_fY *= fValue;
    m_fZ *= fValue;

    return *this;
}

// operator/() - post-divide vector by a scalar
inline Vector3D Vector3D::operator/(const float& fValue) const
{
    Vector3D v3;

    if (Math::isZero(fValue))
    {
        v3.m_fX = 0.0f;
        v3.m_fY = 0.0f;
        v3.m_fZ = 0.0f;
    }
    else 
    {
        float fValue_Inv = 1 / fValue;

        v3.m_fX = v3.m_fX * fValue_Inv;
        v3.m_fY = v3.m_fY * fValue_Inv;
        v3.m_fZ = v3.m_fZ * fValue_Inv;
    }

    return v3;
}

// operator/=() - divide this vector by a scalar
inline Vector3D& Vector3D::operator/=(const float& fValue) 
{
    if (Math::isZero(fValue)) 
    {
        m_fX = 0.0f;
        m_fY = 0.0f;
        m_fZ = 0.0f;
    }
    else 
    {
        float fValue_Inv = 1 / fValue;
        m_fX *= fValue_Inv;
        m_fY *= fValue_Inv;
        m_fZ *= fValue_Inv;
    }

    return *this;
}

// rotateX() - rotate this vector about the X axis
inline Vector3D Vector3D::rotateX(float fRadians) 
{
    Vector3D v3;
    v3.m_fX = m_fX;
    v3.m_fY = m_fY * cos(fRadians) - m_fZ * sin(fRadians);
    v3.m_fZ = m_fY * sin(fRadians) + m_fZ * cos(fRadians);

    return v3;
}

// rotateY() - rotate this vector about the Y axis
inline Vector3D Vector3D::rotateY(float fRadians) 
{
    Vector3D v3;
    v3.m_fX = m_fX * cos(fRadians) + m_fZ * sin(fRadians);
    v3.m_fY = m_fY;
    v3.m_fZ = -m_fX * sin(fRadians) + m_fZ * cos(fRadians);

    return v3;
}

// rotateZ() - rotate this vector about the Z axis
inline Vector3D Vector3D::rotateZ(float fRadians) 
{
    Vector3D v3;

    v3.m_fX = m_fX * cos(fRadians) - m_fY * sin(fRadians);
    v3.m_fY = m_fX * sin(fRadians) + m_fY * cos(fRadians);
    v3.m_fZ = m_fZ;

    return v3;
}

// setPerpendicularXY() - make this vector perpendicular to Vector3D
inline void Vector3D::setPerpendicularXY(Vector3D v3) 
{
    m_fX = -v3.m_fY;
    m_fY = v3.m_fX;
    m_fZ = v3.m_fZ;
}

// setPerpendicularXZ() - make this vector perpendicular to Vector3D
inline void Vector3D::setPerpendicularXZ(Vector3D v3) 
{
    m_fX = -v3.m_fZ;
    m_fY = v3.m_fY;
    m_fZ = v3.m_fX;
}

// setPerpendicularYZ() - make this vector perpendicular to Vector3D
inline void Vector3D::setPerpendicularYZ(Vector3D v3) 
{
    m_fX = v3.m_fX;
    m_fY = -v3.m_fZ;
    m_fZ = v3.m_fY;
}

// cross() - get the cross product of two vectors
inline Vector3D Vector3D::cross(const Vector3D v3) const 
{
    return Vector3D(m_fY * v3.m_fZ - m_fZ * v3.m_fY,
        v3.m_fX * m_fZ - m_fX * v3.m_fZ,
        m_fX * v3.m_fY - m_fY * v3.m_fX);
}

// dot() - return the Dot Product between this vector and another one
inline float Vector3D::dot(const Vector3D v3) const 
{
    return (m_fX * v3.m_fX + m_fY * v3.m_fY + m_fZ * v3.m_fZ);
}

// normalize() - make the length of this vector equal to one
inline void Vector3D::normalize() 
{
    float fMag = sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);

    if (fMag <= Math::ZERO) 
    {
        m_fX = 0.0f;
        m_fY = 0.0f;
        m_fZ = 0.0f;

        return;
    }

    fMag = 1 / fMag;

    m_fX *= fMag;
    m_fY *= fMag;
    m_fZ *= fMag;
}

// isZero() - return true if vector is (0,0,0)
inline bool Vector3D::isZero() const 
{
    if (Math::isZero(m_fX) &&
        Math::isZero(m_fY) &&
        Math::isZero(m_fZ)) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// zero() - set the vector to (0,0,0)
inline void Vector3D::zero() 
{
    m_fX = 0.0f;
    m_fY = 0.0f;
    m_fZ = 0.0f;
}

// getCosAngle() - returns the cos(Angle) value between this vector and vector V. 
// This is less expensive than using getAngle
inline float Vector3D::getCosAngle(const Vector3D& v3, const bool bNormalized) 
{
    // a . b = |a||b|cos(angle)
    // -> cos-1((a.b)/(|a||b|))

    // Make sure we do not divide by zero
    float fMagA = length();
    if (fMagA <= Math::ZERO) 
    {
        // this (A) is an invalid vector
        return 0;
    }

    float fValue = 0;
    if (bNormalized) 
    {
        // v3 is already normalized
        fValue = dot(v3) / fMagA;
    }
    else 
    {
        float fMagB = v3.length();
        if (fMagB <= Math::ZERO) 
        {
            // B is an invalid vector
            return 0;
        }

        fValue = dot(v3) / (fMagA * fMagB);
    }

    // Correct value due To rounding problem
    Math::constrain(-1.0f, 1.0f, fValue);

    return fValue;
}

// getAngle() - return the angle between this vector and vector V in Radians.
// This is more expensive than using getCosAngle
inline float Vector3D::getAngle(const Vector3D& v3, const bool bNormalized, bool bRadians) 
{
    // a . b = |a||b|cos(angle)
    // -> cos-1((a.b)/(|a||b|))

    if (bRadians) 
    {
        return acos(this->getCosAngle(v3));
    }
    else 
    {
        // Convert to degrees
        return Math::radian2Degree(acos(getCosAngle(v3, bNormalized)));
    }
}

// length() - return the absolute length of this vector
inline float Vector3D::length() const 
{
    return sqrtf(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);
}

// length2() - return the relative length of this vector - doesn't use sqrt() and hence is less expensive
inline float Vector3D::length2() const 
{
    return (m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);
}