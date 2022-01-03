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
    const char* file;
    int line;
};

class MemoryProfiler
{
public:
    MemoryProfiler() = default;
    ~MemoryProfiler() = default;

    void NewAllocation(std::size_t size, void* ptr, int line, const char* file);
    void NewFree(void* ptr, int line, const char* file);

    void DumpMemory() const;

private:
    std::array<AllocatedMemory, 2048> m_allocatedMemory;
};
}  // namespace red
