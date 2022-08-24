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

    uint32 GetSize();
    uint32 GetOffset();

private:
    uint8* m_startPtr;
    uint32 m_size;
    uint32 m_stackOffset;
};

class DoubleLinearAllocator
{
public:
    DoubleLinearAllocator(uint32 size);
    ~DoubleLinearAllocator();

    void* Allocate(uint32 size, int count = 1);

    template <typename T>
    T* Allocate(int count = 1);

    void Reset();
    void Swap();

private:
    int m_currentAllocator;
    LinearAllocator m_allocators[2];
};

struct DoubleLinearArrayAllocator
{
    static void* Allocate(uint32 size);
    static void Free(void* ptr);
    static void* Realloc(void* ptr, uint32 oldSize, uint32 size);
};
}  // namespace red

#include "inl/LinearAllocator.inl"