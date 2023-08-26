#pragma once

#include <stdint.h>

#include "MathUtil.h"

namespace yebuk
{
namespace math
{
struct IntVector2
{
    union
    {
        struct
        {
            int32_t X;
            int32_t Y;
        };

        int32_t XY[2];
    };

    IntVector2() : IntVector2(0, 0) {}
    IntVector2(const int32_t x, const int32_t y) : X(x), Y(y) {}
    IntVector2(const uint32_t x, const uint32_t y) : X((int32_t)x), Y((int32_t)y) {}
    IntVector2(const float x, const float y) : IntVector2(MathUtil::Round(x), MathUtil::Round(y)) {}

    inline IntVector2 operator+(const IntVector2& v)
    {
        return IntVector2(X + v.X, Y + v.Y);
    }

    inline IntVector2 operator-(const IntVector2& v)
    {
        return IntVector2(X - v.X, Y - v.Y);
    }

    inline IntVector2 operator*(const IntVector2& v)
    {
        return IntVector2(X * v.X, Y * v.Y);
    }

    inline IntVector2 operator+(const int32_t scalar)
    {
        return IntVector2(X + scalar, Y + scalar);
    }

    inline IntVector2 operator-(const int32_t scalar)
    {
        return IntVector2(X - scalar, Y - scalar);
    }

    inline IntVector2 operator*(const int32_t scalar)
    {
        return IntVector2(X * scalar, Y * scalar);
    }

    inline IntVector2 operator*(const int32_t scalar) const
    {
        return IntVector2(X * scalar, Y * scalar);
    }

    inline IntVector2 operator/(const int32_t scalar)
    {
        return IntVector2(X / scalar, Y / scalar);
    }

    inline IntVector2& operator+=(const IntVector2& v)
    {
        X += v.X;
        Y += v.Y;
        return *this;
    }

    inline IntVector2& operator-=(const IntVector2& v)
    {
        X -= v.X;
        Y -= v.Y;
        return *this;
    }

    inline IntVector2& operator*=(const int32_t scalar)
    {
        X *= scalar;
        Y *= scalar;
        return *this;
    }

    inline IntVector2& operator/=(const int32_t scalar)
    {
        X /= scalar;
        Y /= scalar;
        return *this;
    }

    inline IntVector2 Zero()
    {
        return IntVector2(0, 0);
    }

    inline IntVector2 One()
    {
        return IntVector2(1, 1);
    }
};
}
}