#include "RedEngine/Core/Memory/MemoryUtils.hpp"

#ifdef RED_WINDOWS
#include <memoryapi.h>
#endif

namespace red
{
PageAllocation VirtualAlloc(uint32 size, const PageAllocation* previousAlloc)
{
#ifdef RED_WINDOWS
    auto& systemInfo = GetSystemInfo();
    auto unusedMemory = size % systemInfo.pageSize;
    if (unusedMemory != 0)
    {
        RED_LOG_DEBUG("Virtual allocation ({}) is not aligned to system page size ({}) resulting in {} unused", size,
                      systemInfo.pageSize, unusedMemory);
    }

    void* ptr = ::VirtualAlloc(previousAlloc == nullptr ? nullptr : previousAlloc->ptr, size, MEM_COMMIT | MEM_RESERVE,
                               PAGE_READWRITE);
    RedAssert(ptr != nullptr);

    return {ptr, size};
#else
#error not implemented
#endif
}

void VirtualFree(const PageAllocation& previousAlloc)
{
    ::VirtualFree(previousAlloc.ptr, 0, MEM_RELEASE);
}
}  // namespace red