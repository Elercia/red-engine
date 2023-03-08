#pragma once

#include "RedEngine/Core/Entity/System.hpp"

class b2Contact;

namespace red
{
class PhysicsWorld;
class PhysicBody;
struct Collider;

class PhysicSystem : public System<QueryRW<PhysicBody>>
{
public:
    PhysicSystem(World* world);
    ~PhysicSystem();

    void Init() override;
    void Finalize() override;

    void Update() override;

private:
    void ManageCollisions();
    void ManageTriggers();

private:
    PhysicsWorld* m_physicsWorld;
    float timeStep = 1.0f / 60.f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
};
}  // namespace red