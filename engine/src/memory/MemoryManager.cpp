#include <RedEngine/Engine.hpp>
#include <RedEngine/memory/MemoryManager.hpp>
#include <cstdio>
#include <cstdlib>

#ifdef RED_ENABLE_MEMORY_PROFILING
void* operator new(std::size_t count)
{
    auto& engine = GetRedInstance();

    return engine.GetMemoryManager().Allocate(count);
}

void* operator new[](std::size_t count)
{
    auto& engine = GetRedInstance();

    return engine.GetMemoryManager().AllocateArray(count);
}

void operator delete(void* ptr) noexcept
{
    auto& engine = GetRedInstance();

    return engine.GetMemoryManager().Free(ptr);
}

void operator delete[](void* ptr) noexcept
{
    auto& engine = GetRedInstance();

    return engine.GetMemoryManager().Free(ptr);
}

#endif // RED_USE_MEMORY_MANAGEMENT

namespace red
{
MemoryManager::MemoryManager() : m_memoryProfiler()
{}

MemoryManager::~MemoryManager()
{}

void* MemoryManager::Allocate(std::size_t size)
{
    auto ptr = std::malloc(size);

    m_memoryProfiler.NewAllocation(size, ptr);

    return ptr;
}

void* MemoryManager::AllocateArray(std::size_t size)
{
    auto ptr = std::malloc(size);

    m_memoryProfiler.NewAllocation(size, ptr);

    return ptr;
}

void MemoryManager::Free(void* ptr)
{
    std::free(ptr);

    m_memoryProfiler.NewFree(ptr);
}

void MemoryManager::FreeArray(void* ptr)
{
    std::free(ptr);

    m_memoryProfiler.NewFree(ptr);
}

void MemoryManager::DumpMemory()
{
    m_memoryProfiler.DumpMemory();
}
} // namespace red
