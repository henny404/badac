#pragma once

#ifdef MAP_EXPORTS
#define MAP_API __declspec(dllexport)
#else
#define MAP_API __declspec(dllimport)
#endif

#include <stddef.h>

#include "LinkedList.h"
#include "Core/Public/Util/ChunkedMemoryPool.h"
#include "Core/Public/Util/ArrayUtil.h"

namespace yebuk
{
namespace core
{
namespace containers
{
using namespace yebuk::core::util;

/*
* 단순히 메모리 덩어리만 저장 (생성자, 소멸자 호출 X)
* 사용 전 Initialize() 함수를 호출할 것
* 삽입 시 value == nullptr이면 0 삽입
* KeyValue의 Index를 수정하지 말 것
* value가 포인터 타입인 경우 GetValueOrNull() 호출 시 이중 포인터로 반환
*/
class MAP_API Map final
{
public:
    struct KeyValue
    {
        void* Key;
        void* Value;
        size_t Index;
    };

    struct BucketList
    {
        LinkedListNode* Head;
        LinkedListNode* Tail;
    };

public:
    Map() = default;
    Map(const Map&) = default;
    Map& operator=(const Map&) = default;
    Map(Map&&) = default;
    Map& operator=(Map&&) = default;
    ~Map();

    bool                    Initialize(const size_t keySize, const size_t valueSize, const size_t numMaxElements);
    void                    Release();
    void                    Clear();
    bool                    Insert(const void* key, const size_t keySize, const void* value, const size_t valueSize);
    bool                    Remove(const void* key, const size_t keySize);
    KeyValue*               FindOrNull(const void* key, const size_t keySize) const;

    inline size_t           GetNumElements() const;
    inline size_t           GetNumMaxElements() const;
    inline size_t           GetKeySize() const;
    inline size_t           GetValueSize() const;
    inline size_t           GetBucketSize() const;
    inline float            GetLoadFactor() const;
    inline float            GetMaxLoadFactor() const;
    inline float            GetMinLoadFactor() const;
    void*                   GetValueOrNull(const void* key, const size_t keySize) const;
    inline const KeyValue*  GetKeyValuesPtrOrNull() const;
    size_t                  GetCount(const void* key, const size_t keySize) const;

    inline void             SetMaxLoadFactor(const float loadFactor);
    inline void             SetMinLoadFactor(const float loadFactor);

private:
    bool                    createBucket(const size_t mBucketSizeListIndex);

private:
    size_t                  mKeySize = 0;
    size_t                  mValueSize = 0;
    size_t                  mNumElements = 0;
    size_t                  mBucketSizeIndex = 0;
    size_t                  mBucketSize = 0;
    float                   mMaxLoadFactor = 0.0f;
    float                   mMinLoadFactor = 0.0f;

    BucketList*             mBuckets = nullptr;
    KeyValue*               mKeyValues = nullptr;
    ChunkedMemoryPool*      mNodeMemoryPool = nullptr;
    ChunkedMemoryPool*      mKeyMemoryPool = nullptr;
    ChunkedMemoryPool*      mValueMemoryPool = nullptr;

private:
    static constexpr size_t BUCKET_SIZE_LIST[] =
    {
        7u, 23u, 97u, 397u, 1597u, 6421u, 25717u, 102877u,
        411527u, 879743u, 1799639u, 6584983u, 26339969u, 52679969u
    };
    static constexpr size_t NUM_BUCKET_SIZE_LIST = ARRAY_LENGTH(BUCKET_SIZE_LIST);
    static constexpr float  DEFAULT_MAX_LOAD_FACTOR = 0.75f;
    static constexpr float  DEFAULT_MIN_LOAD_FACTOR = 0.2f;
};

inline size_t Map::GetNumElements() const
{
    return mNumElements;
}

inline size_t Map::GetNumMaxElements() const
{
    return (size_t)(GetBucketSize() * (double)GetMaxLoadFactor() + 1);
}

inline size_t Map::GetKeySize() const
{
    return mKeySize;
}

inline size_t Map::GetValueSize() const
{
    return mValueSize;
}

inline size_t Map::GetBucketSize() const
{
    return mBucketSize;
}

inline float Map::GetLoadFactor() const
{
    return (float)mNumElements / (float)mBucketSize;
}

inline float Map::GetMaxLoadFactor() const
{
    return mMaxLoadFactor;
}

inline float Map::GetMinLoadFactor() const
{
    return mMinLoadFactor;
}

inline const Map::KeyValue* Map::GetKeyValuesPtrOrNull() const
{
    return mKeyValues;
}

inline void Map::SetMaxLoadFactor(const float loadFactor)
{
    mMaxLoadFactor = loadFactor;
}

inline void Map::SetMinLoadFactor(const float loadFactor)
{
    mMinLoadFactor = loadFactor;
}
}
}
}