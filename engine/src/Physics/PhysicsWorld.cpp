#include <RedEngine/Physics/PhysicsWorld.hpp>
#include <RedEngine/Core/Debug/DebugDraw/PhysicsDebugDraw.hpp>

#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include <Box2D/Common/b2Draw.h>

namespace red
{
PhysicsWorld::PhysicsWorld() : m_inernalPhysicsWorld(new b2World({0.f, 0.f})) {}

void PhysicsWorld::InitPhysicsBody(PhysicBody* physicBody,
                                   const PhysicBodyCreationDesc& creationDesc)
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
    m_inernalPhysicsWorld->Step(timeStep, velocityIterations, positionIterations);
}

void PhysicsWorld::ClearForces() { m_inernalPhysicsWorld->ClearForces(); }

std::vector<b2Contact*> PhysicsWorld::GetContacts()
{
    std::vector<b2Contact*> contacts;

    contacts.reserve(m_inernalPhysicsWorld->GetContactCount());
    for (auto* c = m_inernalPhysicsWorld->GetContactList(); c; c = c->GetNext())
    {
        contacts.push_back(c);
    }

    return contacts;
}

void PhysicsWorld::SetDebugDrawer(PhysicsDebugDrawer* drawer)
{
    m_inernalPhysicsWorld->SetDebugDraw(drawer);
}

void PhysicsWorld::DrawDebug() { m_inernalPhysicsWorld->DrawDebugData(); }

}  // namespace red