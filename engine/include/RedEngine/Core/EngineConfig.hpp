#pragma once

// TODO Add a global header to include in every header of red-engine to include vital things like
// DebugMacros, EngineConfigs and so on

#include <RedEngine/Math/Vector.hpp>

#include <cstdint>
#include <cstddef>
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

struct PhysicsInitDesc
{
    Vector2 gravity{0.F, 0.F};
};

/// Struct that represent all the data used by the subEngines to init themselves
struct EngineInitDesc
{
    ConfigurationInitDesc config;
    PhysicsInitDesc physics;
};

}  // namespace red
