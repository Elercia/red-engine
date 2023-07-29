#include "RedEngine/Core/Memory/MemoryProfiler.hpp"

#include "RedEngine/Math/Math.hpp"

#include <iostream>

namespace red
{
#ifdef RED_MEMORY_LEAK_TRACER
AllocationInfo* MemoryProfiler::s_rootAllocation = nullptr;
#endif
MemoryUsageInfo MemoryProfiler::s_memoryUsage;

void* MemoryProfiler::Allocate(sizet size, [[maybe_unused]] int line, [[maybe_unused]] const char* file)
{
    if (size == 0)
    {
        return nullptr;
    }

    const sizet realSize = sizeof(AllocationInfo) + size;
    void* ptr = std::malloc(realSize);

    AllocationInfo* allocInfo = (AllocationInfo*) ptr;
    InitAllocInfo(allocInfo);
    allocInfo->size = size;

#ifdef RED_MEMORY_LEAK_TRACER
    allocInfo->previous = nullptr;

    allocInfo->file = file;
    allocInfo->line = line;
    allocInfo->next = s_rootAllocation;

    if (s_rootAllocation != nullptr)
    {
        RedAssert(s_rootAllocation->previous == nullptr);
        s_rootAllocation->previous = allocInfo;
    }

    s_rootAllocation = allocInfo;
#endif

    s_memoryUsage.currentAllocationCount++;
    s_memoryUsage.currentlyAllocated += size;

    s_memoryUsage.peekAllocationCount++;
    s_memoryUsage.peekAllocated = Math::Max(s_memoryUsage.peekAllocated, s_memoryUsage.currentlyAllocated);

    return (void*) (&allocInfo[1]);
}

void* MemoryProfiler::Realloc(void* ptr, sizet size, int line, const char* file)
{
    if (ptr == nullptr)
        return Allocate(size, line, file);

    if (size == 0)
    {
        Free(ptr);
        return nullptr;
    }

    AllocationInfo* allocInfo = &((AllocationInfo*) ptr)[-1];

    s_memoryUsage.currentlyAllocated -= allocInfo->size;

    const sizet realSize = sizeof(AllocationInfo) + size;
    AllocationInfo* newAlloc = (AllocationInfo*) std::realloc(allocInfo, realSize);
    InitAllocInfo(newAlloc);
    newAlloc->size = size;

    s_memoryUsage.currentlyAllocated += newAlloc->size;
    s_memoryUsage.peekAllocated = Math::Max(s_memoryUsage.peekAllocated, s_memoryUsage.currentlyAllocated);

#ifdef RED_MEMORY_LEAK_TRACER
    RedAssert(allocInfo->start == MemoryGuard);
    RedAssert(allocInfo->end == MemoryGuard);

    AllocationInfo* next = allocInfo->next;
    AllocationInfo* previous = allocInfo->previous;

    newAlloc->next = next;
    newAlloc->previous = previous;

    newAlloc->file = file;
    newAlloc->line = line;

    RedAssert(newAlloc->start == MemoryGuard);
    RedAssert(newAlloc->end == MemoryGuard);

    if (next != nullptr)
    {
        RedAssert(next->previous == allocInfo);
        next->previous = newAlloc;
    }

    if (previous != nullptr)
    {
        RedAssert(previous->next == allocInfo);
        previous->next = newAlloc;
    }
    else
    {
        RedAssert(s_rootAllocation == allocInfo);
        // the only without previous is the root
        s_rootAllocation = newAlloc;
    }
#endif

    return (void*) (&newAlloc[1]);
}

void MemoryProfiler::Free(void* ptr)
{
    if (ptr == nullptr)
        return;

    AllocationInfo* allocInfo = &((AllocationInfo*) ptr)[-1];

#ifdef RED_MEMORY_LEAK_TRACER

    RedAssert(allocInfo->start == MemoryGuard);
    RedAssert(allocInfo->end == MemoryGuard);

    if (allocInfo->next != nullptr)
    {
        RedAssert(allocInfo->next->previous == allocInfo);
        allocInfo->next->previous = allocInfo->previous;
    }

    if (allocInfo->previous != nullptr)
    {
        RedAssert(allocInfo->previous->next == allocInfo);
        allocInfo->previous->next = allocInfo->next;
    }
    else
    {
        RedAssert(s_rootAllocation == allocInfo);
        // the only without previous is the root
        s_rootAllocation = allocInfo->next;
    }
#endif

    s_memoryUsage.currentAllocationCount--;
    s_memoryUsage.currentlyAllocated -= allocInfo->size;

    std::free(allocInfo);
}

MemoryUsageInfo MemoryProfiler::GetUsage()
{
    return s_memoryUsage;
}

void MemoryProfiler::ResetUsage()
{
    s_memoryUsage = MemoryUsageInfo();
}

void MemoryProfiler::InitAllocInfo(AllocationInfo* info)
{
    info->size = 0;

#ifdef RED_MEMORY_LEAK_TRACER
    info->line = 0;
    info->file = "";
#endif

    info->next = nullptr;
    info->previous = nullptr;
}
}  // namespace red
