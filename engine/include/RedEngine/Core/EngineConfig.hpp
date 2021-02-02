#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <cstddef>
#include <cstdint>
#include <string>

#ifndef RED_NO_MEMORY_PROFILING
#define RED_ENABLE_MEMORY_PROFILING
#endif

namespace red
{
using ComponentId_t = uint32_t;
using EntityId_t = uint32_t;

constexpr std::size_t ComponentPoolSize = 2048;

struct ConfigurationInitDesc
{
    int argc{0};
    char** argv;
    std::string resourceFolder;
};

/// Struct that represent all the data used by the subEngines to init themselves
struct EngineInitDesc
{
    ConfigurationInitDesc config;
};

}  // namespace red
