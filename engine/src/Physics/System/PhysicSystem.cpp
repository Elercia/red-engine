#include "RedEngine/Core/Components/Transform.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"

#include <Box2D/b2_Contact.h>

namespace red
{
PhysicSystem::PhysicSystem(World* world) : System(world), m_physicsWorld(world->GetPhysicsWorld()) {}

PhysicSystem::~PhysicSystem() {}

void PhysicSystem::Init() { ManageEntities(); }

void PhysicSystem::ManageEntities()
{
    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* physicBody = entity->GetComponent<PhysicBody>();

        if (physicBody->m_status == ComponentStatus::VALID)
            continue;

        const auto& creationDesc = physicBody->m_desc;

        m_physicsWorld->InitPhysicsBody(physicBody, creationDesc);

        physicBody->m_status = ComponentStatus::VALID;
    }

    for (auto* entity : GetComponents<ColliderList>())
    {
        auto* colliderList = entity->GetComponent<ColliderList>();
        if (colliderList->m_status == ComponentStatus::VALID)
            continue;

        auto* physicBody = entity->GetComponentInParent<PhysicBody>(true);
        if (!physicBody)
        {
            RED_LOG_WARNING("Collider list added without parenting physicbody (in {})", entity->GetName());
            continue;
        }

        colliderList->m_attachedPhysicBody = physicBody;

        auto* fixture = physicBody->GetBody()->GetFixtureList();
        while (fixture)
        {
            physicBody->GetBody()->DestroyFixture(fixture);
            fixture = fixture->GetNext();
        }

        for (auto& p : colliderList->GetColliders())
        {
            auto& collider = p.second;
            collider.m_fixture = physicBody->GetBody()->CreateFixture(&(collider.m_fixtureDef));
        }

        colliderList->m_status = ComponentStatus::VALID;
    }
}

void PhysicSystem::Finalise()
{
    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* physicBody = entity->GetComponent<PhysicBody>();

        m_physicsWorld->DestroyPhysicsBody(physicBody);  // Destroying a body will destroy all the fixture attached
    }
}

void PhysicSystem::Update()
{
    // m_physicsWorld->ClearForces();

    ManageEntities();

    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* transform = entity->GetComponent<Transform>();
        auto* physicBody = entity->GetComponent<PhysicBody>();

        physicBody->GetBody()->SetTransform(ConvertToPhysicsVector(transform->GetPosition()), 0);
    }

    m_physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* transform = entity->GetComponent<Transform>();
        auto* physicBody = entity->GetComponent<PhysicBody>();

        transform->SetPosition(ConvertFromPhysicsVector(physicBody->GetBody()->GetPosition()));
    }

    ManageCollisions();
    ManageTriggers();
}

void PhysicSystem::ManageCollisions()
{
    auto& collisions = m_physicsWorld->GetCollisions();

    for (auto& constCollision : collisions)
    {
        auto collision = constCollision;  // copy

        collision.firstPhysicBody->m_collisionSignal.emit(collision);

        collision.SwapFirstSecond();

        collision.firstPhysicBody->m_collisionSignal.emit(collision);
    }
}

void PhysicSystem::ManageTriggers()
{
    auto& triggers = m_physicsWorld->GetTriggers();

    for (auto& constTrigger : triggers)
    {
        auto triggerInfo = constTrigger;  // copy

        triggerInfo.firstPhysicBody->m_triggerSignal(triggerInfo);

        triggerInfo.SwapFirstSecond();

        triggerInfo.secondPhysicBody->m_triggerSignal(triggerInfo);
    }
}
}  // namespace red