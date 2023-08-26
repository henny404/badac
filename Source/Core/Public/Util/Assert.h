#pragma once

#include <intrin.h>

#if defined(_DEBUG)
#define ASSERT(cond, msg) { if (!(cond)) { __debugbreak(); } }
#else
#define ASSERT(cond, msg) { }
#endif