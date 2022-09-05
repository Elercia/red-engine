#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/Level.hpp"

namespace perf
{
class PerfLevel : public red::Level
{
public:
    explicit PerfLevel(red::World* world) : red::Level("PerfLevel", world){};
    ~PerfLevel() override = default;

    void Init() override;
    void Finalize() override;
};
}  // namespace perf
