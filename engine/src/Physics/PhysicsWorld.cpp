#include "RedEngine/Physics/PhysicsWorld.hpp"

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"

#include <Box2D/Common/b2Draw.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Dynamics/b2World.h>

namespace red
{
PhysicsWorld::PhysicsWorld() : m_inernalPhysicsWorld(new b2World({0.f, 0.f}))
{
    m_inernalPhysicsWorld->SetContactListener(this);
}

void PhysicsWorld::InitPhysicsBody(PhysicBody* physicBody, const PhysicBodyCreationDesc& creationDesc)
{
    b2BodyDef bodyDef;

    bodyDef.userData = physicBody;

    switch (creationDesc.type)
    {
        case PhysicsBodyType::DYNAMIC_BODY:
            bodyDef.type = b2_dynamicBody;
            break;
        case PhysicsBodyType::STATIC_BODY:
            bodyDef.type = b2_staticBody;
            break;
        case PhysicsBodyType::KINEMATIC_BODY:
            bodyDef.type = b2_kinematicBody;
            break;
    }

    physicBody->m_body = m_inernalPhysicsWorld->CreateBody(&bodyDef);
}

void PhysicsWorld::DestroyPhysicsBody(PhysicBody* physicBody)
{
    m_inernalPhysicsWorld->DestroyBody(physicBody->GetBody());
}

void PhysicsWorld::Step(float timeStep, int32 velocityIterations, int32 positionIterations)
{
    UpdateContactInfos();

    m_inernalPhysicsWorld->Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsWorld::ClearForces() { m_inernalPhysicsWorld->ClearForces(); }

const std::vector<red::CollisionInfo>& PhysicsWorld::GetCollisions() const { return m_frameCollisionInfo; }

const std::vector<red::TriggerInfo>& PhysicsWorld::GetTriggers() const { return m_frameTriggerInfo; }

void PhysicsWorld::SetDebugDrawer(PhysicsDebugDrawer* drawer) { m_inernalPhysicsWorld->SetDebugDraw(drawer); }

void PhysicsWorld::DrawDebug() { m_inernalPhysicsWorld->DrawDebugData(); }

void PhysicsWorld::PreSolve(b2Contact* contact, const b2Manifold* /*oldManifold*/)
{
    const auto* manifold = contact->GetManifold();

    if (manifold->pointCount == 0)
    {
        return;
    }

    auto* physicBody1 = static_cast<PhysicBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
    auto* physicBody2 = static_cast<PhysicBody*>(contact->GetFixtureB()->GetBody()->GetUserData());

    auto* collider1 = static_cast<Collider*>(contact->GetFixtureA()->GetUserData());
    auto* collider2 = static_cast<Collider*>(contact->GetFixtureB()->GetUserData());

    if (collider1->IsTrigger() || collider2->IsTrigger())
    {
        AddTriggerContact(physicBody1, physicBody2, collider1, collider2);
    }
    else
    {
        AddCollisionContact(physicBody1, physicBody2, collider1, collider2, contact);
    }
}

void PhysicsWorld::UpdateContactInfos()
{
    m_frameCollisionInfo.clear();
    m_frameTriggerInfo.clear();
}

void PhysicsWorld::AddCollisionContact(PhysicBody* physicBody1, PhysicBody* physicBody2, Collider* collider1,
                                       Collider* collider2, const b2Contact* contact)
{
    auto* manifold = contact->GetManifold();

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    CollisionInfo collisionInfo;
    collisionInfo.firstPhysicBody = physicBody1;
    collisionInfo.secondPhysicBody = physicBody2;
    collisionInfo.firstCollider = collider1;
    collisionInfo.secondCollider = collider2;
    collisionInfo.restitution = contact->GetRestitution();
    collisionInfo.tangentSpeed = contact->GetTangentSpeed();
    collisionInfo.normal = ConvertFromPhysicsVector(worldManifold.normal);

    for (int i = 0; i < manifold->pointCount; i++)
    {
        auto& manifoldPoint = manifold->points[i];
        collisionInfo.contactPoints.push_back({ConvertFromPhysicsVector(manifoldPoint.localPoint),
                                               manifoldPoint.normalImpulse, manifoldPoint.tangentImpulse});
    }

    m_frameCollisionInfo.push_back(std::move(collisionInfo));
}

void PhysicsWorld::AddTriggerContact(PhysicBody* physicBody1, PhysicBody* physicBody2, Collider* collider1,
                                     Collider* collider2)
{
    TriggerInfo collisionInfo;
    collisionInfo.firstPhysicBody = physicBody1;
    collisionInfo.secondPhysicBody = physicBody2;
    collisionInfo.firstCollider = collider1;
    collisionInfo.secondCollider = collider2;

    m_frameTriggerInfo.push_back(std::move(collisionInfo));
}
}  // namespace red