#include "RedEngine/Core/Memory/MemoryUtils.hpp"

#ifdef RED_WINDOWS
#define NOMINMAX 1
#include <memoryapi.h>
#endif

#ifdef RED_LINUX
#include <sys/mman.h>
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

#elif defined(RED_LINUX)
    void* ptr = ::mmap(previousAlloc == nullptr ? nullptr : previousAlloc->ptr, size, PROT_READ | PROT_WRITE,
                       MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

    RedAssert(ptr != MAP_FAILED);
#else
#error not implemented
#endif

    return {ptr, size};
}

void VirtualFree(const PageAllocation& previousAlloc)
{
#ifdef RED_WINDOWS
    ::VirtualFree(previousAlloc.ptr, 0, MEM_RELEASE);
#elif defined(RED_LINUX)
    ::munmap(previousAlloc.ptr, previousAlloc.size);
#else
#error not implemented
#endif
}
}  // namespace red