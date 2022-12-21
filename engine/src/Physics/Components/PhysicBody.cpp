#include "RedEngine/Physics/Components/PhysicBody.hpp"

#include "RedEngine/Physics/PhysicsModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(PhysicBody)

PhysicBody::PhysicBody(Entity* entity) : Component(entity), m_desc(), m_body(nullptr), m_nextColliderIndex(0)
{
}

PhysicBody::PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc)
    : Component(entity), m_desc(desc), m_body(nullptr)
{
    entity->GetWorld()->GetPhysicsWorld()->InitPhysicsBody(this, m_desc);
}

PhysicBody::~PhysicBody()
{
}

void PhysicBody::ApplyForce(const Vector2& force, const Vector2& relativePosition)
{
    auto worldPosition = ConvertFromPhysicsVector(m_body->GetPosition()) + relativePosition;

    m_body->ApplyForce(ConvertToPhysicsVector(force), ConvertToPhysicsVector(worldPosition), true);
}

b2Body* PhysicBody::GetBody()
{
    return m_body;
}

void PhysicBody::SetBody(b2Body* body)
{
    m_body = body;
}

int PhysicBody::AddCollider(Collider&& collider, const ColliderDesc& desc)
{
    auto insertionResult = m_colliders.insert({m_nextColliderIndex++, std::move(collider)});

    // Set the used data to the right collider
    auto& mapPair = insertionResult.first;
    auto& colliderInserted = mapPair->second;

    b2FixtureUserData userData;
    userData.pointer = (uintptr_t) &colliderInserted;
    colliderInserted.m_fixtureDef.userData = userData;
    colliderInserted.m_fixtureDef.isSensor = desc.isTrigger;
    colliderInserted.m_fixtureDef.restitution = desc.restitution;
    colliderInserted.m_fixtureDef.friction = desc.friction;
    colliderInserted.m_fixtureDef.density = 1.0f;
    colliderInserted.m_fixture = m_body->CreateFixture(&colliderInserted.m_fixtureDef);

    return mapPair->first;
}

int PhysicBody::AddCircleCollider(const CircleColliderDesc& desc)
{
    Collider collider;

    b2CircleShape shape;
    shape.m_p = ConvertToPhysicsVector(desc.center);
    shape.m_radius = ConvertToPhysicsDistance(desc.radius);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int PhysicBody::AddEdgeCollider(const EdgeColliderDesc& desc)
{
    Collider collider;

    b2EdgeShape shape;
    shape.SetTwoSided(ConvertToPhysicsVector(desc.start), ConvertToPhysicsVector(desc.end));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int PhysicBody::AddPolygonCollider(const PolygonColliderDesc& desc)
{
    Collider collider;

    b2PolygonShape shape;
    Array<b2Vec2> b2Points;
    b2Points.resize(desc.points.size());
    std::transform(desc.points.begin(), desc.points.end(), b2Points.begin(),
                   [](Vector2 v) -> b2Vec2 { return ConvertToPhysicsVector(v); });

    shape.Set(b2Points.data(), static_cast<int32>(b2Points.size()));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

void PhysicBody::RemoveCollider(int id)
{
    auto it = m_colliders.find(id);

    if (it != m_colliders.end())
    {
        m_body->DestroyFixture(it->second.m_fixture);
        m_colliders.erase(it);
    }
}

Map<ColliderId, Collider>& PhysicBody::GetColliders()
{
    return m_colliders;
}

const Map<ColliderId, Collider>& PhysicBody::GetColliders() const
{
    return m_colliders;
}

}  // namespace red
