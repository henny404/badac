#pragma once

#ifdef MATH_UTIL_EXPORTS
#define MATH_UTIL_API __declspec(dllexport)
#else
#define MATH_UTIL_API __declspec(dllimport)
#endif

#include <stdint.h>

namespace yebuk
{
namespace math
{
class MATH_UTIL_API MathUtil final
{
public:
	MathUtil() = delete;
	MathUtil(const MathUtil&) = delete;
	MathUtil& operator=(const MathUtil&) = delete;
	MathUtil(MathUtil&&) = delete;
	MathUtil& operator=(MathUtil&&) = delete;
	~MathUtil() = default;

public:
	template <typename T>
	static inline const T& Min(const T& a, const T& b)
	{
		return (a <= b) ? a : b;
	}

	template <typename T>
	static inline const T& Max(const T& a, const T& b)
	{
		return (a >= b) ? a : b;
	}

	static int32_t Abs(const int32_t x);
	static float Absf(const float x);
	static int32_t Round(const float x);
};
}
}