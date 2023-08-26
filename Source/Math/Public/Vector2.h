#pragma once

#include <stdint.h>

namespace yebuk
{
namespace math
{
struct Vector2
{
    union
    {
        struct
        {
            float X;
            float Y;
        };

        float XY[2];
    };

    Vector2() : Vector2(0.0f, 0.0f) {}
    Vector2(const int32_t x, const int32_t y) : Vector2((float)x, (float)y) {}
    Vector2(const uint32_t x, const uint32_t y) : Vector2((float)x, (float)y) {}
    Vector2(const float x, const float y) : X(x), Y(y) {}

    inline Vector2 operator+(const Vector2& v)
    {
        return Vector2(X + v.X, Y + v.Y);
    }

    inline Vector2 operator+(const Vector2& v) const
    {
        return Vector2(X + v.X, Y + v.Y);
    }

    inline Vector2 operator-(const Vector2& v)
    {
        return Vector2(X - v.X, Y - v.Y);
    }

    inline Vector2 operator-(const Vector2& v) const
    {
        return Vector2(X - v.X, Y - v.Y);
    }

    inline Vector2 operator*(const Vector2& v)
    {
        return Vector2(X * v.X, Y * v.Y);
    }

    inline Vector2 operator+(const float scalar)
    {
        return Vector2(X + scalar, Y + scalar);
    }

    inline Vector2 operator-(const float scalar)
    {
        return Vector2(X - scalar, Y - scalar);
    }

    inline Vector2 operator*(const float scalar)
    {
        return Vector2(X * scalar, Y * scalar);
    }

    inline Vector2 operator*(const float scalar) const
    {
        return Vector2(X * scalar, Y * scalar);
    }

    inline Vector2 operator/(const float scalar)
    {
        return Vector2(X / scalar, Y / scalar);
    }

    inline Vector2& operator+=(const Vector2& v)
    {
        X += v.X;
        Y += v.Y;
        return *this;
    }

    inline Vector2& operator-=(const Vector2& v)
    {
        X -= v.X;
        Y -= v.Y;
        return *this;
    }

    inline Vector2& operator*=(const float scalar)
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    inline Vector2& operator/=(const float scalar)
    {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    inline Vector2 Zero()
    {
        return Vector2(0, 0);
    }

    inline Vector2 One()
    {
        return Vector2(1, 1);
    }
};
}
}