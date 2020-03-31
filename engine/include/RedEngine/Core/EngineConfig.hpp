#pragma once

#include <cstdint>

#ifndef RED_NO_MEMORY_PROFILING
#define RED_ENABLE_MEMORY_PROFILING
#endif

namespace red
{
using ComponentName_t = const char*;
using ComponentId_t = uint32_t;
using EntityId_t = uint32_t;
}  // namespace red
