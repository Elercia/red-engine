#include "RedEngine/Core/Memory/MemoryProfiler.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include <iostream>

namespace red
{
// TODO what is this ? remake it completely
void MemoryProfiler::NewAllocation(std::size_t size, void* ptr, int /*line*/, const char* /*file*/)
{
    for (auto& profile : m_allocatedMemory)
    {
        if (profile.ptr == nullptr)
        {
            profile = {ptr, size};
            break;
        }
    }
}

void MemoryProfiler::NewFree(void* ptr, int /*line*/, const char* /*file*/)
{
    for (auto& profile : m_allocatedMemory)
    {
        if (profile.ptr == ptr)
        {
            profile = {nullptr, 0};
            break;
        }
    }
}

void MemoryProfiler::DumpMemory() const
{
    std::cout << "=================== MEMORY DUMP ===================" << std::endl;

    uint64_t dumpMemorySize = 0;

    for (const auto& profile : m_allocatedMemory)
    {
        if (profile.ptr != nullptr)
        {
            dumpMemorySize += profile.size;
            std::cout << "Memory : " << profile.ptr << " of size " << profile.size << " octets" << std::endl;
        }
    }

    std::cout << "==================== RESULT ======================" << std::endl;
    std::cout << "Size : " << dumpMemorySize << " octets" << std::endl;
    std::cout << "==================================================" << std::endl;
}
}  // namespace red
