#pragma once

#include <cstdint>

/// Define this to disable the memory manager for global new operators
#ifndef RED_DISABLE_MEMORY_PROFILING

#define RED_ENABLE_MEMORY_PROFILING

#endif // !RED_NOT_USING_MEMORY_MANAGEMENT

namespace red
{
using ComponentName_t = uint32_t;
using ComponentId_t = uint32_t;
using EntityId_t = int;
} // namespace red
