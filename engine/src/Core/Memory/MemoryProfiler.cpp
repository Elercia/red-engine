#include "RedEngine/Core/Memory/MemoryProfiler.hpp"

#include <iostream>

namespace red
{
AllocationInfo* MemoryProfiler::s_rootAllocation = nullptr;
MemoryUsageInfo MemoryProfiler::s_memoryUsage;

void* MemoryProfiler::Allocate(sizet size, int line, const char* file)
{
    if (size == 0)
    {
        return nullptr;
    }

    const sizet realSize = sizeof(AllocationInfo) + size;
    void* ptr = std::malloc(realSize);

    AllocationInfo* allocInfo = (AllocationInfo*) ptr;
    InitAllocInfo(allocInfo);
    allocInfo->file = file;
    allocInfo->line = line;
    allocInfo->size = size;

    allocInfo->next = s_rootAllocation;
    allocInfo->previous = nullptr;

    if (s_rootAllocation != nullptr)
    {
        RedAssert(s_rootAllocation->previous == nullptr);
        s_rootAllocation->previous = allocInfo;
    }

    s_rootAllocation = allocInfo;

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

    RedAssert(allocInfo->start == MemoryGuard);
    RedAssert(allocInfo->end == MemoryGuard);

    AllocationInfo* next = allocInfo->next;
    AllocationInfo* previous = allocInfo->previous;

    const sizet realSize = sizeof(AllocationInfo) + size;
    AllocationInfo* newAlloc = (AllocationInfo*) std::realloc(allocInfo, realSize);
    InitAllocInfo(newAlloc);

    newAlloc->next = next;
    newAlloc->previous = previous;

    newAlloc->size = size;
    newAlloc->file = file;
    newAlloc->line = line;

    s_memoryUsage.currentlyAllocated += newAlloc->size;
    s_memoryUsage.peekAllocated = Math::Max(s_memoryUsage.peekAllocated, s_memoryUsage.currentlyAllocated);

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

    return (void*) (&newAlloc[1]);
}

void MemoryProfiler::Free(void* ptr)
{
    if (ptr == nullptr)
        return;

    AllocationInfo* allocInfo = &((AllocationInfo*) ptr)[-1];

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

    s_memoryUsage.currentAllocationCount--;
    s_memoryUsage.currentlyAllocated -= allocInfo->size;

    std::free(allocInfo);
}

const MemoryUsageInfo& MemoryProfiler::GetUsage()
{
    return s_memoryUsage;
}

void MemoryProfiler::ResetUsage()
{
    s_memoryUsage = MemoryUsageInfo();
}

void MemoryProfiler::InitAllocInfo(AllocationInfo* info)
{
    info->start = MemoryGuard;
    info->end = MemoryGuard;

    info->size = 0;
    info->line = 0;
    info->file = "";

    info->next = nullptr;
    info->previous = nullptr;
}
}  // namespace red
