#include <RedEngine/Physics/System/PhysicsSystem.hpp>
#include <RedEngine/Physics/Components/PhysicBody.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>
#include <RedEngine/Core/Components/Transform.hpp>

namespace red
{
PhysicSystem::PhysicSystem(World* world) : System(world), m_physicsWorld(world->GetPhysicsWorld())
{
}

PhysicSystem::~PhysicSystem() {}

void PhysicSystem::Init()
{
    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* physicBody = entity->GetComponent<PhysicBody>();

        if (physicBody->m_status == ComponentStatus::VALID)
            continue;

        const auto& creationDesc = physicBody->m_desc;

        b2BodyDef bodyDef;

        bodyDef.userData = this;

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

        physicBody->m_body = m_world->GetPhysicsWorld()->CreateBody(&bodyDef);

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
            RED_LOG_WARNING("Collider list added without parenting physicbody (in {})",
                            entity->GetName());
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

        m_physicsWorld->DestroyBody(
            physicBody->m_body);  // Destroying a body will destroy all the fixture attached
    }
}

void PhysicSystem::Update()
{
    b2World* physicsWorld = m_world->GetPhysicsWorld();

    // physicsWorld->ClearForces();

    Init();

    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* transform = entity->GetComponent<Transform>();
        auto* physicBody = entity->GetComponent<PhysicBody>();

        physicBody->GetBody()->SetTransform(ConvertToPhysicsVector(transform->GetPosition()), 0);
    }

    physicsWorld->Step(timeStep, velocityIterations, positionIterations);

    for (auto* entity : GetComponents<PhysicBody>())
    {
        auto* transform = entity->GetComponent<Transform>();
        auto* physicBody = entity->GetComponent<PhysicBody>();

        transform->SetPosition(ConvertFromPhysicsVector(physicBody->GetBody()->GetPosition()));
    }
}

}  // namespace red