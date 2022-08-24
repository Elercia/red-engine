#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
class LinearAllocator
{
public:
    explicit LinearAllocator(uint32 size);
    ~LinearAllocator();

    void* Allocate(uint32 size, int count = 1);

    template <typename T>
    T* Allocate(int count = 1);

    void Reset();

private:
    uint8* m_startPtr;
    uint32 m_size;
    uint32 m_stackOffset;
};
}  // namespace red

#include "inl/LinearAllocator.inl"