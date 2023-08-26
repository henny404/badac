#pragma once

#ifdef HASH_FUNCTIONS_EXPORTS
#define HASH_FUNCTIONS_API __declspec(dllexport)
#else
#define HASH_FUNCTIONS_API __declspec(dllimport)
#endif

#include <stddef.h>
#include <stdint.h>

namespace yebuk
{
namespace core
{
namespace util
{
namespace hash_function
{
extern "C" HASH_FUNCTIONS_API uint32_t FNV32(const char* bytes, const size_t len);
}
}
}
}