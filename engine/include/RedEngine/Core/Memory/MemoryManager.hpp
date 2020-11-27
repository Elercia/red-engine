#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <cstddef>

#include "MemoryProfiler.hpp"
#include <RedEngine/Core/SubEngine.hpp>

namespace red
{
    //TODO make something of it ?
class MemoryManager : public SubEngine
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
