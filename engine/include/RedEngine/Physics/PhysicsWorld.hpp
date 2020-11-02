#pragma once

#include <RedEngine/Physics/Components/PhysicBody.hpp>

#include <memory>

class b2World;

namespace red
{
class PhysicsDebugDrawer;

class PhysicsWorld
{
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    void InitPhysicsBody(PhysicBody* physicBody, const PhysicBodyCreationDesc& creationDesc);
    void DestroyPhysicsBody(PhysicBody* physicBody);

    void Step(float timeStep, int32 velocityIterations, int32 positionIterations);

    void ClearForces();

    std::vector<b2Contact*> GetContacts();

    void SetDebugDrawer(PhysicsDebugDrawer* drawer);
    void DrawDebug();

private:
    std::unique_ptr<b2World> m_inernalPhysicsWorld;
};
}  // namespace red