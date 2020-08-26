#include <RedEngine/Physics/Components/PhysicBody.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>

namespace red
{
PhysicBody::PhysicBody(Entity* entity, PhysicsBodyType bodyType) : Component(entity)
{
    b2BodyDef bodyDef;

    bodyDef.userData = this;

    switch (bodyType)
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

    m_body = entity->GetWorld()->GetPhysicsWorld()->CreateBody(&bodyDef);
}

PhysicBody::~PhysicBody() {}

void PhysicBody::Finalize() { m_owner->GetWorld()->GetPhysicsWorld()->DestroyBody(m_body); }

void PhysicBody::AddCollider(ColliderList* colliderList)
{
    PhysicBodyColliderHolder holder{
        colliderList,                                                                  //
        colliderList->OnColliderAdded.Connect(&PhysicBody::OnColliderAdded, this),     //
        colliderList->OnColliderRemoved.Connect(&PhysicBody::OnColliderRemoved, this)  //
    };

    m_colliders.push_back(holder);
}

void PhysicBody::RemoveCollider(ColliderList* colliderList)
{
    auto holderIt =
        std::find_if(m_colliders.begin(), m_colliders.end(),
                     [colliderList](auto holder) { return colliderList == holder.colliderList; });

    holderIt->addedSlot->Deactivate();
    holderIt->RemovedSlot->Deactivate();

    m_colliders.erase(holderIt);
}

void PhysicBody::OnColliderAdded(Collider* collider)
{
    collider->m_fixture = m_body->CreateFixture(&collider->m_fixtureDef);
}

void PhysicBody::OnColliderRemoved(Collider* collider)
{
    m_body->DestroyFixture(collider->m_fixture);
}

b2Body* PhysicBody::GetBody() { return m_body; }

}  // namespace red
