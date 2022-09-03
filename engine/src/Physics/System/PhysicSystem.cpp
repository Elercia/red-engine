#include "RedEngine/Physics/PhysicsModule.hpp"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Physics/Components/Collider.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"

#include <box2d/b2_contact.h>

namespace red
{
PhysicSystem::PhysicSystem(World* world) : System(world), m_physicsWorld(world->GetPhysicsWorld())
{
}

PhysicSystem::~PhysicSystem()
{
}

void PhysicSystem::Init()
{
    System::Init();
    ManageEntities();
}

void PhysicSystem::ManageEntities()
{
    PROFILER_EVENT_CATEGORY("PhysicSystem::ManageEntities", ProfilerCategory::Physics)

    auto bodies = GetComponents<PhysicBody>();
    for (auto* entity : bodies)
    {
        auto* physicBody = entity->GetComponent<PhysicBody>();

        if (physicBody->m_status == ComponentStatus::VALID)
            continue;

        const auto& creationDesc = physicBody->m_desc;

        m_physicsWorld->InitPhysicsBody(physicBody, creationDesc);

        physicBody->m_status = ComponentStatus::VALID;
    }

    auto colliders = GetComponents<ColliderList>();
    for (auto* entity : colliders)
    {
        auto* colliderList = entity->GetComponent<ColliderList>();
        if (colliderList->m_status == ComponentStatus::VALID)
            continue;

        auto* physicBody = entity->GetComponentInParent<PhysicBody>(true);
        if (physicBody == nullptr)
        {
            RED_LOG_WARNING("Collider list added without parenting physicbody (in {})", entity->GetName());
            continue;
        }

        colliderList->m_attachedPhysicBody = physicBody;

        auto* fixture = physicBody->GetBody()->GetFixtureList();
        while (fixture != nullptr)
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
    auto bodies =  GetComponents<PhysicBody>();
    for (auto* entity :bodies)
    {
        auto* physicBody = entity->GetComponent<PhysicBody>();

        m_physicsWorld->DestroyPhysicsBody(physicBody);  // Destroying a body will destroy all the fixture attached
    }
}

void PhysicSystem::Update()
{
    PROFILER_EVENT_CATEGORY("PhysicSystem::Update", ProfilerCategory::Physics)

    m_physicsWorld->ClearForces();

    ManageEntities();

    auto bodies =  GetComponents<PhysicBody>();
    for (auto* entity : bodies)
    {
        auto* transform = entity->GetComponent<Transform>();
        auto* physicBody = entity->GetComponent<PhysicBody>();

        physicBody->GetBody()->SetTransform(ConvertToPhysicsVector(transform->GetPosition()), 0);
    }

    m_physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    for (auto* entity : bodies)
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
    PROFILER_EVENT_CATEGORY("PhysicSystem::ManageCollisions", ProfilerCategory::Physics)

    for (const auto& constCollision : m_physicsWorld->GetCollisions())
    {
        auto collision = constCollision;  // copy

        collision.firstPhysicBody->m_collisionSignal.emit(collision);

        collision.SwapFirstSecond();

        collision.firstPhysicBody->m_collisionSignal.emit(collision);
    }
}

void PhysicSystem::ManageTriggers()
{
    PROFILER_EVENT_CATEGORY("PhysicSystem::ManageTriggers", ProfilerCategory::Physics)

    const auto& triggers = m_physicsWorld->GetTriggers();

    for (const auto& constTrigger : triggers)
    {
        auto triggerInfo = constTrigger;  // copy

        triggerInfo.firstPhysicBody->m_triggerSignal(triggerInfo);

        triggerInfo.SwapFirstSecond();

        triggerInfo.secondPhysicBody->m_triggerSignal(triggerInfo);
    }
}
}  // namespace red