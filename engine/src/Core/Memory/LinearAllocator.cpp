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
}  // namespace red
