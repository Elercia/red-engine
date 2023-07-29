#include "RedEngine/Core/Memory/PoolAllocator.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
VirtualPoolAllocator::VirtualPoolAllocator(uint32 sizeOfElement, int initialCapacity)
    : m_blockSize(sizeOfElement), m_capacity(0), m_currentAllocationCount(0), m_nextFreeBlock(nullptr)
{
    Realloc(initialCapacity);
}

VirtualPoolAllocator::~VirtualPoolAllocator()
{
    VirtualFree(m_pageAlloc);
}

void VirtualPoolAllocator::Realloc(uint32 newCapacity)
{
    if (newCapacity <= m_capacity)
    {
        RED_LOG_ERROR("Realloc of a smaller capacity");
        return;
    }

    auto newAllocStartOffset = m_capacity * (m_blockSize + (uint32) sizeof(FreeBlock));
    auto sizeOfAlloc = newCapacity * (m_blockSize + (uint32) sizeof(FreeBlock));

    m_pageAlloc = VirtualAlloc(sizeOfAlloc, nullptr);

    memset((uint8*) m_pageAlloc.ptr + newAllocStartOffset, 0, sizeOfAlloc - newAllocStartOffset);

    // Utility function to have a ptr from a index
    auto GetFreeblock = [this](uint32 index) -> FreeBlock*
    {
        auto offset = index * (sizeof(FreeBlock) + m_blockSize);
        return (FreeBlock*) ((uint8*) (m_pageAlloc.ptr) + offset);
    };

    for (auto i = newCapacity - m_capacity; i < newCapacity - 1; i++)
    {
        auto* block = GetFreeblock(i);
        block->nextFreeBlock = GetFreeblock(i + 1);
    }

    auto* last = GetFreeblock(newCapacity - 1);
    last->nextFreeBlock = m_nextFreeBlock;

    m_nextFreeBlock = (FreeBlock*) ((uint8*) (m_pageAlloc.ptr) + newAllocStartOffset);

    m_capacity = newCapacity;
}

void* VirtualPoolAllocator::AllocateElement()
{
    if (m_nextFreeBlock == nullptr)
    {
        Grow();
    }

    void* ptr = (void*) (m_nextFreeBlock + 1);

    m_nextFreeBlock = m_nextFreeBlock->nextFreeBlock;
    m_currentAllocationCount++;

    RedAssert(ptr != nullptr);

    return ptr;
}

void VirtualPoolAllocator::FreeElement(void* ptr)
{
    m_currentAllocationCount--;

    FreeBlock* freeBlock = &((FreeBlock*) ptr)[-1];

    if (m_nextFreeBlock == nullptr)
    {
        m_nextFreeBlock = freeBlock;
    }
    else
    {
        freeBlock->nextFreeBlock = m_nextFreeBlock;
        m_nextFreeBlock = freeBlock;
    }
}

void VirtualPoolAllocator::Grow()
{
    Realloc(m_capacity * 2);
}
}  // namespace red
