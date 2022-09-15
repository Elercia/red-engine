#include "RedEngine/Core/Memory/PoolAllocator.hpp"

namespace red
{
VirtualPoolAllocator::VirtualPoolAllocator(uint32 sizeOfElement, int nbOfElement)
    : m_blockSize(sizeOfElement), m_nbElements(nbOfElement), m_nextFreeBlock(nullptr)
{
    Realloc();
}

VirtualPoolAllocator::~VirtualPoolAllocator()
{
    VirtualFree(m_pageAlloc);
}

void VirtualPoolAllocator::Realloc()
{
    auto sizeOfAlloc = (m_blockSize * m_nbElements) + (m_nbElements * (uint32) sizeof(FreeBlock));

    m_pageAlloc = VirtualAlloc(sizeOfAlloc, nullptr);
    memset(m_pageAlloc.ptr, 0, sizeOfAlloc);

    auto GetFreeblock = [this](uint32 index) -> FreeBlock*
    {
        auto offset = index * sizeof(FreeBlock) + index * m_blockSize;
        return (FreeBlock*) ((uint8*) (m_pageAlloc.ptr) + offset);
    };

    for (auto i = 0u; i < m_nbElements - 1; i++)
    {
        auto* block = GetFreeblock(i);
        block->nextFreeBlock = GetFreeblock(i + 1);
    }

    m_nextFreeBlock = (FreeBlock*) (m_pageAlloc.ptr);

    auto* last = GetFreeblock(m_nbElements);
    last->nextFreeBlock = nullptr;
}

void* VirtualPoolAllocator::AllocateElement()
{
    if (m_nextFreeBlock == nullptr)
    {
        RED_LOG_ERROR("OutOfMemory in virtual allocator");
        return nullptr;
    }

    void* ptr = (void*)(m_nextFreeBlock + 1);

    m_nextFreeBlock = m_nextFreeBlock->nextFreeBlock;

    RedAssert(ptr != nullptr);

    return ptr;
}

void VirtualPoolAllocator::FreeElement(void* ptr)
{
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
}  // namespace red
