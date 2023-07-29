#pragma once

#include "RedEngine/Utils/Types.hpp"

namespace red
{
struct PageAllocation
{
    void* ptr;
    uint32 size;
};

PageAllocation VirtualAlloc(uint32 size, const PageAllocation* previousAlloc);
void VirtualFree(const PageAllocation& ptr);
}  // namespace red