#pragma once

#include <RedEngine/EngineConfig.hpp>
#include <RedEngine/memory/MemoryProfiler.hpp>
#include <RedEngine/memory/PoolAllocator.hpp>
#include <cstddef>

namespace red
{
class MemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();

    void* Allocate(std::size_t size);
    void* AllocateArray(std::size_t size);

    void Free(void* ptr);
    void FreeArray(void* ptr);

    void DumpMemory();

private:
    MemoryProfiler m_memoryProfiler;
};
}  // namespace red

#ifdef RED_ENABLE_MEMORY_PROFILING
void* operator new(std::size_t count);
void* operator new[](std::size_t count);

void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;
#endif  // RED_ENABLE_MEMORY_PROFILING
