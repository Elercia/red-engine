#pragma once

#include <cstdint>

#ifndef RED_NO_MEMORY_PROFILING
#define RED_ENABLE_MEMORY_PROFILING
#endif

namespace red
{
using ComponentId_t = uint32_t;
using EntityId_t = uint32_t;

constexpr std::size_t ComponentPoolSize = 2048;

constexpr EntityId_t MaxPersistentEntities = 30;
}  // namespace red
