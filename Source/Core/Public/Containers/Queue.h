#pragma once

#ifdef QUEUE_EXPORTS
#define QUEUE_API __declspec(dllexport)
#else
#define QUEUE_API __declspec(dllimport)
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
class QUEUE_API Queue final
{
public:
    Queue() = default;
    Queue(const Queue&) = default;
    Queue& operator=(const Queue&) = default;
    Queue(Queue&&) = default;
    Queue& operator=(Queue&&) = default;
    ~Queue();

    bool                Initialize(const size_t elementSize, const size_t numMaxElements);
    void                Release();
    void                Clear();
    bool                Enqueue(const void* element, const size_t elementSize);
    bool                Dequeue();

    inline size_t       GetNumElements() const;
    inline size_t       GetNumMaxElements() const;
    inline size_t       GetElementSize() const;
    inline const void*  GetElementsPtrOrNull() const;
    void*               PeekOrNull() const;

private:
    size_t              mElementSize = 0;
    size_t              mNumElements = 0;
    size_t              mNumMaxElements = 0;
    size_t              mFront = 0;
    size_t              mBack = 0;
    char*               mElements = nullptr;
};

inline size_t Queue::GetNumElements() const
{
    return mNumElements;
}

inline size_t Queue::GetNumMaxElements() const
{
    return mNumMaxElements;
}

inline size_t Queue::GetElementSize() const
{
    return mElementSize;
}

inline const void* Queue::GetElementsPtrOrNull() const
{
    return mElements;
}
}
}
}