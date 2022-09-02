#pragma once

#include "RedEngine/Utils/Types.hpp"

#include <array>
#include <cstddef>

#define RED_MEMORY_PROFILER
#ifdef RED_MEMORY_PROFILER
#define red_malloc(size)       red::MemoryProfiler::Allocate(size, __LINE__, __FILE__)
#define red_realloc(ptr, size) red::MemoryProfiler::Realloc(ptr, size, __LINE__, __FILE__)
#define red_free(ptr)          red::MemoryProfiler::Free(ptr)

#define red_new(T, ...) red::MemoryProfiler::New<T>(__LINE__, __FILE__, ##__VA_ARGS__)
#define red_delete(ptr) red::MemoryProfiler::Delete(ptr)
#else
#define red_malloc(size)       std::malloc(size)
#define red_realloc(ptr, size) std::realloc(ptr, size)
#define red_free(ptr)          std::free(ptr)

#define red_new(T, ...) new T(##__VA_ARGS__)
#define red_delete(ptr) delete ptr
#endif

#define MemoryGuard (uint32) 0xBAADF00D

namespace red
{
struct AllocationInfo
{
    uint32 start;

    std::size_t size;
    int line;
    const char* file;

    AllocationInfo* next;
    AllocationInfo* previous;

    uint32 end;
};

struct MemoryUsageInfo
{
    uint64 currentlyAllocated = 0;
    uint64 peekAllocated = 0;

    uint64 currentAllocationCount = 0;
    uint64 peekAllocationCount = 0;
};

class MemoryProfiler
{
public:
    static void* Allocate(sizet size, int line, const char* file);
    static void* Realloc(void* ptr, sizet size, int line, const char* file);
    static void Free(void* ptr);

    template <typename T, typename... Args>
    static T* New(int line, const char* file, Args... args);

    template <typename T>
    static void Delete(T* ptr);

    static void InitAllocInfo(AllocationInfo* info);

    static const MemoryUsageInfo& GetUsage();
    static void ResetUsage();

private:
    MemoryProfiler() = default;
    ~MemoryProfiler() = default;

    static AllocationInfo* s_rootAllocation;
    static MemoryUsageInfo s_memoryUsage;
};
}  // namespace red

#include "inl/MemoryProfiler.inl"
