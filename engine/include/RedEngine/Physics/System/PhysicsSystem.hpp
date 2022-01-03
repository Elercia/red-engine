#pragma once

#include "RedEngine/Core/Entity/System.hpp"

class b2Contact;

namespace red
{
class PhysicsWorld;
class PhysicBody;
struct Collider;

class PhysicSystem : public System
{
public:
    PhysicSystem(World* world);
    ~PhysicSystem();

    void Init() override;
    void Finalise() override;

    void Update() override;

    virtual void ManageEntities() override;

private:
    void ManageCollisions();
    void ManageTriggers();

private:
    PhysicsWorld* m_physicsWorld;
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 10;
    int32 positionIterations = 8;
};
}  // namespace red