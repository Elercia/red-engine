#include "RedEngine/Physics/PhysicsWorld.hpp"

#include "RedEngine/Physics/PhysicsModule.hpp"

#include "RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"

#include <box2d/b2_contact.h>
#include <box2d/b2_draw.h>
#include <box2d/b2_world.h>

namespace red
{
PhysicsWorld::PhysicsWorld() : m_internalPhysicsWorld(new b2World({0.f, 0.f}))
{
    m_internalPhysicsWorld->SetContactListener(this);
}

void PhysicsWorld::InitPhysicsBody(PhysicBody* physicBody, const PhysicBodyCreationDesc& creationDesc)
{
    b2BodyDef bodyDef;

    b2BodyUserData userData;
    userData.pointer = (uintptr_t) physicBody;
    bodyDef.userData = userData;
    bodyDef.allowSleep = false;

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

    physicBody->m_body = m_internalPhysicsWorld->CreateBody(&bodyDef);
}

void PhysicsWorld::DestroyPhysicsBody(PhysicBody* physicBody)
{
    if (physicBody->GetBody() == nullptr)
        return;

    m_internalPhysicsWorld->DestroyBody(physicBody->GetBody());
    physicBody->SetBody(nullptr);
}

void PhysicsWorld::Step(float timeStep, int32 velocityIterations, int32 positionIterations)
{
    UpdateContactInfos();

    m_internalPhysicsWorld->Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsWorld::ClearForces()
{
    m_internalPhysicsWorld->ClearForces();
}

const Array<CollisionInfo>& PhysicsWorld::GetCollisions() const
{
    return m_frameCollisionInfo;
}

const Array<TriggerInfo>& PhysicsWorld::GetTriggers() const
{
    return m_frameTriggerInfo;
}

void PhysicsWorld::SetDebugDrawer(PhysicsDebugDrawer* drawer)
{
    m_internalPhysicsWorld->SetDebugDraw(drawer);
}

void PhysicsWorld::DrawDebug()
{
    m_internalPhysicsWorld->DebugDraw();
}

void PhysicsWorld::PreSolve(b2Contact* contact, const b2Manifold* /*oldManifold*/)
{
    const auto* manifold = contact->GetManifold();

    if (manifold->pointCount == 0)
    {
        return;
    }

    auto* physicBody1 = reinterpret_cast<PhysicBody*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto* physicBody2 = reinterpret_cast<PhysicBody*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    auto* collider1 = reinterpret_cast<Collider*>(contact->GetFixtureA()->GetUserData().pointer);
    auto* collider2 = reinterpret_cast<Collider*>(contact->GetFixtureB()->GetUserData().pointer);

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
    const auto* manifold = contact->GetManifold();

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
        const auto& manifoldPoint = manifold->points[i];
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

    m_frameTriggerInfo.push_back(collisionInfo);
}
}  // namespace red