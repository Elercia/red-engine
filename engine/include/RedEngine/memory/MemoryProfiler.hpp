#pragma once

#include <array>
#include <cstddef>

namespace red
{
struct AllocatedMemory
{
    friend class MemoryProfiler;

    void* ptr;
    std::size_t size;
};

class MemoryProfiler
{
public:
    MemoryProfiler() = default;
    ~MemoryProfiler() = default;

    void NewAllocation(std::size_t size, void* ptr);
    void NewFree(void* ptr);

    void DumpMemory();

private:
    std::array<AllocatedMemory, 2048> m_allocatedMemory;
};
}  // namespace red
