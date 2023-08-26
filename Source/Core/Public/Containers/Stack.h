#pragma once

#ifdef STACK_EXPORTS
#define STACK_API __declspec(dllexport)
#else
#define STACK_API __declspec(dllimport)
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
class STACK_API Stack final
{
public:
    Stack() = default;
    Stack(const Stack&) = default;
    Stack& operator=(const Stack&) = default;
    Stack(Stack&&) = default;
    Stack& operator=(Stack&&) = default;
    ~Stack();

    bool                Initialize(const size_t elementSize, const size_t numMaxElements);
    void                Release();
    void                Clear();
    bool                Push(const void* element, const size_t elementSize);
    bool                Pop();

    inline size_t       GetNumElements() const;
    inline size_t       GetNumMaxElements() const;
    inline size_t       GetElementSize() const;
    inline const void*  GetElementsPtrOrNull() const;
    void*               TopOrNull() const;

private:
    size_t              mElementSize = 0;
    size_t              mNumElements = 0;
    size_t              mNumMaxElements = 0;
    char*               mElements = nullptr;
};

inline size_t Stack::GetNumElements() const
{
    return mNumElements;
}

inline size_t Stack::GetNumMaxElements() const
{
    return mNumMaxElements;
}

inline size_t Stack::GetElementSize() const
{
    return mElementSize;
}

inline const void* Stack::GetElementsPtrOrNull() const
{
    return mElements;
}
}
}
}