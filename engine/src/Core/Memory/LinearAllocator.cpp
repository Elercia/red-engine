#include "RedEngine/Core/Memory/LinearAllocator.hpp"

namespace red
{
LinearAllocator::LinearAllocator(uint32 size) : m_startPtr(nullptr), m_size(size), m_stackOffset(0)
{
    m_startPtr = (uint8*) red_malloc(size);
}

LinearAllocator::~LinearAllocator()
{
    red_free(m_startPtr);
}

void* LinearAllocator::Allocate(uint32 size, int count)
{
    const uint32 allocationSize = size * count;

    if ((m_stackOffset + allocationSize) > m_size)
    {
        RED_LOG_ERROR("No more memory inside linear allocator");
        return nullptr;
    }

    uint8* ptr = m_startPtr + m_stackOffset;
    m_stackOffset += allocationSize;

    return ptr;
}

void LinearAllocator::Reset()
{
    m_stackOffset = 0;
}

uint32 LinearAllocator::GetSize()
{
    return m_size;
}

uint32 LinearAllocator::GetOffset()
{
    return m_stackOffset;
}

DoubleLinearAllocator::DoubleLinearAllocator(uint32 size)
    : m_currentAllocator(0), m_allocators{LinearAllocator(size), LinearAllocator(size)}
{
}

DoubleLinearAllocator::~DoubleLinearAllocator()
{
}

void* DoubleLinearAllocator::Allocate(uint32 size, int count /*= 1*/)
{
    return m_allocators[m_currentAllocator].Allocate(size, count);
}

void DoubleLinearAllocator::Reset()
{
    m_allocators[m_currentAllocator].Reset();
}

void DoubleLinearAllocator::Swap()
{
    m_currentAllocator = (m_currentAllocator + 1) % 2;
    Reset();
}

void* DoubleLinearArrayAllocator::Allocate(uint32 size)
{
    auto threadId = Thread::GetCurrentThread().GetId();
    auto& allocator = Engine::GetInstance()->GetThreadFrameAllocator(threadId);
    return allocator.Allocate(size);
}

void DoubleLinearArrayAllocator::Free(void* /*ptr*/)
{
}

void* DoubleLinearArrayAllocator::Realloc(void* ptr, uint32 oldSize, uint32 size)
{
    auto* ret = Engine::GetInstance()->GetThreadFrameAllocator(Thread::GetCurrentThread().GetId()).Allocate(size);

    if (ptr != nullptr && ret != nullptr)
        memcpy(ret, ptr, oldSize);

    return ret;
}

}  // namespace red
