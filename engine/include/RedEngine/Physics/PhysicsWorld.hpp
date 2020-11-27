#pragma once

#include <RedEngine/Physics/Components/PhysicBody.hpp>

#include <memory>

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class b2World;

namespace red
{
class PhysicsDebugDrawer;

class PhysicsWorld : public b2ContactListener
{
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    void InitPhysicsBody(PhysicBody* physicBody, const PhysicBodyCreationDesc& creationDesc);
    void DestroyPhysicsBody(PhysicBody* physicBody);

    void Step(float timeStep, int32 velocityIterations, int32 positionIterations);

    void ClearForces();

    const std::vector<CollisionInfo>& GetCollisions() const;
    const std::vector<TriggerInfo>& GetTriggers() const;

    void SetDebugDrawer(PhysicsDebugDrawer* drawer);
    void DrawDebug();

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

private:
    void UpdateContactInfos();
    void AddTriggerContact(PhysicBody* physicBody1, PhysicBody* physicBody2,
                                            Collider* collider1, Collider* collider2,
                                            const b2Contact* contact);
    void AddCollisionContact(PhysicBody* physicBody1, PhysicBody* physicBody2,
                                              Collider* collider1, Collider* collider2,
                                              const b2Contact* contact);

private:
    std::unique_ptr<b2World> m_inernalPhysicsWorld;

    std::vector<CollisionInfo> m_frameCollisionInfo;
    std::vector<TriggerInfo> m_frameTriggerInfo;
};
}  // namespace red