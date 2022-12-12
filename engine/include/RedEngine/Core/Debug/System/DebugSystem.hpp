#pragma once

#include "RedEngine/Core/Entity/System.hpp"

namespace red
{
class DebugComponent;

class DebugSystem : public System
{
public:
    explicit DebugSystem(World* world);
    ~DebugSystem() override = default;

    virtual void Init() override;

    void Update() override;

private:

    static void RenderConsole(DebugComponent* debug);
    static void RenderEntityTree(DebugComponent* debug);
    static void RenderDebugPhysicsControls(DebugComponent* debug);
};
}  // namespace red
