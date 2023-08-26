#pragma once

#include <cstdint>
#include <type_traits>
#include <new>

#include "StaticMemoryPool.h"

// class, struct 타입만 가능
// 기본 생성자가 있어야 함
template <typename ElementType>
class ObjectPool final : public StaticMemoryPool
{
public:
    ObjectPool() = default;
    ObjectPool(const ObjectPool&) = default;
    ObjectPool& operator=(const ObjectPool&) = default;
    ObjectPool(ObjectPool&&) = default;
    ObjectPool& operator=(ObjectPool&&) = default;
    virtual ~ObjectPool()
    {
        Release();
    }

    bool Initialize(const uint32_t numElementsPerChunk, const uint32_t numChunks)
    {
        if (!StaticMemoryPool::Initialize(sizeof(ElementType), numElementsPerChunk, numChunks))
        {
            ASSERT(false, L"Failed to create memory pool");
            return false;
        }

        // 생성자 호출
        if constexpr (!std::is_fundamental<ElementType>::value)
        {
            for (uint32_t i = 0; i < mNumCurChunks; ++i)
            {
                for (uint32_t j = 0; j < mNumElementsPerChunk; ++j)
                {
                    ElementType* element = (ElementType*)(mMemoryPoolChunks[i] + j * (mElementSize + sizeof(StaticMemoryPool::Header)) + sizeof(StaticMemoryPool::Header));
                    new(element) ElementType;
                }
            }
        }

        return true;
    }

    void Release()
    {
        if (mMemoryPoolChunks == nullptr)
        {
            return;
        }

        // 소멸자 호출
        if constexpr (!std::is_fundamental<ElementType>::value)
        {
            for (uint32_t i = 0; i < mNumCurChunks; ++i)
            {
                for (uint32_t j = 0; j < mNumElementsPerChunk; ++j)
                {
                    ElementType* element = (ElementType*)(mMemoryPoolChunks[i] + j * (mElementSize + sizeof(StaticMemoryPool::Header)) + sizeof(StaticMemoryPool::Header));
                    element->~ElementType();
                }
            }
        }

        StaticMemoryPool::Release();
    }

    void* AllocateOrNull()
    {
        static uint32_t prevNumChunks = mNumCurChunks;

        ElementType* element = (ElementType*)StaticMemoryPool::AllocateOrNull();
        if (element == nullptr)
        {
            return nullptr;
        }

        if (mNumCurChunks > prevNumChunks)
        {
            if constexpr (!std::is_fundamental<ElementType>::value)
            {
                // 생성자 호출
                for (uint32_t i = 0; i < mNumElementsPerChunk; ++i)
                {
                    ElementType* element = (ElementType*)(mMemoryPoolChunks[prevNumChunks] + i * (mElementSize + sizeof(StaticMemoryPool::Header)) + sizeof(StaticMemoryPool::Header));
                    new(element) ElementType;
                }
            }

            prevNumChunks = mNumCurChunks;
        }

        return element;
    }
};