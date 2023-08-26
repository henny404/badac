#pragma once

#ifdef CHUNKED_MEMORY_POOL_EXPORTS
#define CHUNKED_MEMORY_POOL_API __declspec(dllexport)
#else
#define CHUNKED_MEMORY_POOL_API __declspec(dllimport)
#endif

#include <stddef.h>

#include "Core/Public/Containers/LinkedList.h"

namespace yebuk
{
namespace core
{
namespace util
{
using namespace yebuk::core::containers;

class CHUNKED_MEMORY_POOL_API ChunkedMemoryPool final
{
private:
    enum State
    {
        STATE_ALLOC = 0x95,
        STATE_DEALLOC = 0x85
    };

    struct Chunk
    {
        char* Blocks;
        size_t* IndexTable;
        size_t* IndexTablePointer;
    };

    struct Header
    {
        State State;
        Chunk* Chunk;
    };

public:
    ChunkedMemoryPool() = default;
    ChunkedMemoryPool(const ChunkedMemoryPool&) = default;
    ChunkedMemoryPool& operator=(const ChunkedMemoryPool&) = default;
    ChunkedMemoryPool(ChunkedMemoryPool&&) = default;
    ChunkedMemoryPool& operator=(ChunkedMemoryPool&&) = default;
    ~ChunkedMemoryPool();

    bool                Initialize(const size_t elementSize, const size_t numElementsPerchunk);
    void                Release();

    void* AllocateOrNull();
    void                Deallocate(void* block);
    void                Reset();

private:
    bool                createChunk();

private:
    size_t              mElementSize = 0;
    size_t              mBlockSize = 0;
    size_t              mNumElementsPerChunk = 0;

    LinkedListNode* mHead = nullptr;
    LinkedListNode* mTail = nullptr;
};
}
}
}