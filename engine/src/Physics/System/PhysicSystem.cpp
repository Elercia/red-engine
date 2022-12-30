#include "RedEngine/Physics/PhysicsModule.hpp"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
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
}

void PhysicSystem::Finalise()
{
    auto bodies =  GetComponents<PhysicBody>();
    for (auto& tuple :bodies)
    {
        auto* physicBody = std::get<1>( tuple );

        m_physicsWorld->DestroyPhysicsBody(physicBody);  // Destroying a body will destroy all the fixture attached
    }
}

void PhysicSystem::Update()
{
    PROFILER_EVENT_CATEGORY("PhysicSystem::Update", ProfilerCategory::Physics)

    m_physicsWorld->ClearForces();

    auto bodies = GetComponents<PhysicBody>();
    for (auto& tuple : bodies)
    {
        auto* transform = std::get<0>( tuple )->GetComponent<Transform>();
        auto* physicBody = std::get<1>( tuple );

        if (physicBody->IsStatic())
        {
            continue;
        }

        transform->SetLocked(true);

        // FIXME : Manage object scale. Need to scale the different fixtures of the body
        physicBody->GetBody()->SetTransform(ConvertToPhysicsVector(transform->GetLocalPosition()),
                                            transform->GetLocalRotationRad());
    }

    m_physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    for (auto& tuple : bodies)
    {
        auto* transform = std::get<0>( tuple )->GetComponent<Transform>();
        auto* physicBody = std::get<1>( tuple );

        if (physicBody->IsStatic())
        {
            continue;
        }

        transform->SetLocked(false);

        transform->SetLocalPosition(ConvertFromPhysicsVector(physicBody->GetBody()->GetPosition()));
        transform->SetLocalRotationRad(physicBody->GetBody()->GetAngle());
        transform->UpdateWorldMatrixIfNeeded();
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