#pragma once

#include <RedEngine/Core/Entity/System.hpp>

namespace red
{
class PhysicSystem : public System
{
public:
    PhysicSystem(World* world);
    ~PhysicSystem();

    void FixedUpdate() override;

private:
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
};
}  // namespace red