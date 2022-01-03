#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class DebugSystem : public System
{
public:
    explicit DebugSystem(World* world);
    ~DebugSystem() override = default;

    virtual void Init() override;

    void Update() override;
};
}  // namespace red
