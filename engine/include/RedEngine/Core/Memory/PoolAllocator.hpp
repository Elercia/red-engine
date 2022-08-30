#pragma once

#include "RedEngine/Utils/Types.hpp"
#include "RedEngine/Core/Memory/MemoryUtils.hpp"

#include <utility>

namespace red
{
class VirtualPoolAllocator
{
public:
    VirtualPoolAllocator(uint32 sizeOfElement, int nbOfElement);
    ~VirtualPoolAllocator();

    void Realloc();

    void* AllocateElement();
    void FreeElement(void* ptr);

    template <typename T, typename ...Args>
    T* Allocate(Args&& ... args);

    template <typename T>
    void Free(T* ptr);

private:
    struct FreeBlock
    {
        FreeBlock* nextFreeBlock = nullptr;
    };

    uint32 m_blockSize;
    uint32 m_nbElements;
    PageAllocation m_pageAlloc;

    FreeBlock* m_nextFreeBlock;
};
}  // namespace red

#include "inl/PoolAllocator.inl"