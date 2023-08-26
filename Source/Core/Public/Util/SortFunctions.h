#pragma once

#ifdef SORT_FUNCTIONS_EXPORTS
#define SORT_FUNCTIONS_API __declspec(dllexport)
#else
#define SORT_FUNCTIONS_API __declspec(dllimport)
#endif

#include <stddef.h>

namespace yebuk
{
namespace core
{
namespace util
{
namespace sort_function
{
    extern "C" SORT_FUNCTIONS_API void QuickSort(void* elements, const size_t elementSize, const size_t left, const size_t right);
    extern "C" SORT_FUNCTIONS_API void SelectionSort(void* elements, const size_t elementSize, const size_t numElements);
}
}
}
}