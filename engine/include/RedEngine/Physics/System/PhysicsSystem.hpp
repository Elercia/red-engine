#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <RedEngine/Core/Entity/System.hpp>

namespace red
{
class PhysicSystem : public System
{
public:
    PhysicSystem(World* world);
    ~PhysicSystem();

    void Init() override;
    void Finalise() override;

    void Update() override;

private:
    b2World* m_physicsWorld;
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
};
}  // namespace red