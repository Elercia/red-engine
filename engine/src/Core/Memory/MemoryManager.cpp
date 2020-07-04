#include "RedEngine/Core/Memory/MemoryManager.hpp"

#include <cstdio>
#include <cstdlib>

#include "RedEngine/Core/Engine.hpp"

namespace red
{
MemoryManager::MemoryManager() : m_memoryProfiler() {}

MemoryManager::~MemoryManager() {}

void* MemoryManager::Allocate(std::size_t size, int line, const char* file)
{
    auto ptr = std::malloc(size);

#ifdef RED_ENABLE_MEMORY_PROFILING
    m_memoryProfiler.NewAllocation(size, ptr, line, file);
#endif
    return ptr;
}

void* MemoryManager::AllocateArray(std::size_t size, int line, const char* file)
{
    auto ptr = std::malloc(size);

#ifdef RED_ENABLE_MEMORY_PROFILING
    m_memoryProfiler.NewAllocation(size, ptr, line, file);
#endif
    return ptr;
}

void MemoryManager::Free(void* ptr, int line, const char* file)
{
    std::free(ptr);

#ifdef RED_ENABLE_MEMORY_PROFILING
    m_memoryProfiler.NewFree(ptr, line, file);
#endif
}

void MemoryManager::FreeArray(void* ptr, int line, const char* file)
{
    std::free(ptr);

#ifdef RED_ENABLE_MEMORY_PROFILING
    m_memoryProfiler.NewFree(ptr, line, file);
#endif
}

void MemoryManager::DumpMemory() const
{
#ifdef RED_ENABLE_MEMORY_PROFILING
    m_memoryProfiler.DumpMemory();
#endif
}
}  // namespace red
