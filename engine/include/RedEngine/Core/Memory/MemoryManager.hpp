#pragma once

#include "RedEngine/Core/Memory/MemoryProfiler.hpp"

#include <cstddef>

namespace red
{
// TODO make something of it ?
class MemoryManager
{
public:
    MemoryManager();
    ~MemoryManager();

    void* Allocate(std::size_t size, int line = __LINE__, const char* file = __FILE__);
    void* AllocateArray(std::size_t size, int line = __LINE__, const char* file = __FILE__);

    void Free(void* ptr, int line = __LINE__, const char* file = __FILE__);
    void FreeArray(void* ptr, int line = __LINE__, const char* file = __FILE__);

    void DumpMemory() const;

private:
    MemoryProfiler m_memoryProfiler;
};
}  // namespace red
