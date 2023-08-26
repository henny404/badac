#pragma once

#ifdef STATIC_MEMORY_POOL_EXPORTS
#define STATIC_MEMORY_POOL_API __declspec(dllexport)
#else
#define STATIC_MEMORY_POOL_API __declspec(dllimport)
#endif

#include <stddef.h>
#include <stdint.h>

namespace yebuk
{
namespace core
{
namespace util
{
class STATIC_MEMORY_POOL_API StaticMemoryPool
{
protected:
    enum Status
    {
        STATUS_ALLOC = 0x95,
        STATUS_DEALLOC = 0x85
    };

    struct Header
    {
        union
        {
            struct
            {
                uint32_t Status : 8;
                uint32_t ChunkIndex : 24;
            } Flag;

            uint32_t Signature;
        };
    };

public:
    StaticMemoryPool();
    StaticMemoryPool(const StaticMemoryPool& rhs);
    StaticMemoryPool& operator=(const StaticMemoryPool& rhs);
    StaticMemoryPool(StaticMemoryPool&&) = default;
    StaticMemoryPool& operator=(StaticMemoryPool&&) = default;
    virtual ~StaticMemoryPool();

    virtual bool Initialize(const size_t elementSize, const size_t numElementsPerChunk, const size_t numChunks);
    virtual void Release();

    virtual void* AllocateOrNull();
    virtual void Deallocate(void* block);
    void Reset();

private:
    bool createChunk();

protected:
    char** mMemoryPoolChunks = nullptr;
    size_t** mIndexTableChunks = nullptr;
    size_t** mIndexTablePointerChunks = nullptr;

    size_t mElementSize = 0;
    size_t mNumElementsPerChunk = 0;
    size_t mNumChunks = 0;
    size_t mNumCurChunks = 0;
};
}
}
}