#pragma once

#ifdef FIXED_VECTOR_EXPORTS
#define FIXED_VECTOR_API __declspec(dllexport)
#else
#define FIXED_VECTOR_API __declspec(dllimport)
#endif

#include <stddef.h>

namespace yebuk
{
namespace core
{
namespace containers
{
/*
* 단순히 메모리 덩어리만 저장 (생성자, 소멸자 호출 X)
* 사용 전 Initialize() 함수를 호출할 것
* element == nullptr이면 0 삽입
*/
class FIXED_VECTOR_API FixedVector final
{
public:
    FixedVector() = default;
    FixedVector(const FixedVector&) = default;
    FixedVector& operator=(const FixedVector&) = default;
    FixedVector(FixedVector&&) = default;
    FixedVector& operator=(FixedVector&&) = default;
    ~FixedVector();

    bool                Initialize(const size_t elementSize, const size_t numMaxElements);
    void                Release();
    void                Clear();
    inline bool         PushBack(const void* element, const size_t elementSize);
    inline bool         PopBack();
    bool                Insert(const size_t index, const void* element, const size_t elementSize);
    bool                RemoveByIndex(const size_t index);
    bool                RemoveByElement(const void* element, const size_t elementSize);

    inline size_t       GetNumElements() const;
    inline size_t       GetNumMaxElements() const;
    inline size_t       GetElementSize() const;
    inline const void*  GetElementsPtrOrNull() const;
    inline void*        GetElementsPtrOrNull();
    inline void*        GetBackOrNull() const;
    void*               GetElementOrNull(const size_t index) const;

private:
    size_t              mElementSize = 0;
    size_t              mNumElements = 0;
    size_t              mNumMaxElements = 0;
    char*               mElements = nullptr;
};

// element == nullptr이면 0 삽입
inline bool FixedVector::PushBack(const void* element, const size_t elementSize)
{
    return Insert(GetNumElements(), element, elementSize);
}

inline bool FixedVector::PopBack()
{
    return RemoveByIndex(GetNumElements() - 1);
}

inline size_t FixedVector::GetNumElements() const
{
    return mNumElements;
}

inline size_t FixedVector::GetNumMaxElements() const
{
    return mNumMaxElements;
}

inline size_t FixedVector::GetElementSize() const
{
    return mElementSize;
}

inline const void* FixedVector::GetElementsPtrOrNull() const
{
    return mElements;
}

inline void* FixedVector::GetElementsPtrOrNull()
{
    return mElements;
}

inline void* FixedVector::GetBackOrNull() const
{
    return GetElementOrNull(GetNumElements() - 1);
}
}
}
}