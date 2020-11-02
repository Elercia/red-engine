#include <RedEngine/Physics/System/PhysicsSystem.hpp>
#include <RedEngine/Physics/Components/PhysicBody.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>
#include <RedEngine/Core/Components/Transform.hpp>
#include <RedEngine/Physics/ContactInfo.hpp>

#include <Box2D/Dynamics/Contacts/b2Contact.h>

namespace red
{
PhysicSystem::PhysicSystem(World* world) : System(world), m_physicsWorld(world->GetPhysicsWorld())
{
}

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

        m_physicsWorld->DestroyPhysicsBody(physicBody);  // Destroying a body will destroy all the fixture attached
    }
}

void PhysicSystem::Update()
{
    m_physicsWorld->ClearForces();

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

    ManageContacts();
}

void PhysicSystem::ManageContacts()
{
    auto& contacts = m_physicsWorld->GetContacts();

    for (const auto& contact : contacts)
    {
        auto* physicBody1 =
            static_cast<PhysicBody*>(contact->GetFixtureA()->GetBody()->GetUserData());
        auto* physicBody2 =
            static_cast<PhysicBody*>(contact->GetFixtureB()->GetBody()->GetUserData());

        auto* collider1 = static_cast<Collider*>(contact->GetFixtureA()->GetUserData());
        auto* collider2 = static_cast<Collider*>(contact->GetFixtureB()->GetUserData());

        // const auto* manifold = contact->GetManifold();

        if (contact->IsTouching())
        {
            ManageTriggerContact(physicBody1, physicBody2, collider1, collider2, contact);
        }
        else
        {
            ManageCollisionContact(physicBody1, physicBody2, collider1, collider2, contact);
        }
    }
}

void PhysicSystem::ManageCollisionContact(PhysicBody* physicBody1, PhysicBody* physicBody2,
                                          Collider* collider1, Collider* collider2,
                                          const b2Contact* contact)
{
    CollisionInfo collisionInfo;
    collisionInfo.firstPhysicBody = physicBody1;
    collisionInfo.secondPhysicBody = physicBody2;
    collisionInfo.firstCollider = collider1;
    collisionInfo.secondCollider = collider2;
    collisionInfo.restitution = contact->GetRestitution();
    collisionInfo.tangentSpeed = contact->GetTangentSpeed();

    physicBody1->m_collisionSignal(collisionInfo);
    collisionInfo.SwapFirstSecond();
    physicBody2->m_collisionSignal(collisionInfo);
}

void PhysicSystem::ManageTriggerContact(PhysicBody* physicBody1, PhysicBody* physicBody2,
                                        Collider* collider1, Collider* collider2,
                                        const b2Contact* contact)
{
    TriggerInfo collisionInfo;
    collisionInfo.firstPhysicBody = physicBody1;
    collisionInfo.secondPhysicBody = physicBody2;
    collisionInfo.firstCollider = collider1;
    collisionInfo.secondCollider = collider2;

    physicBody1->m_triggerSignal(collisionInfo);
    collisionInfo.SwapFirstSecond();
    physicBody2->m_triggerSignal(collisionInfo);
}

}  // namespace red