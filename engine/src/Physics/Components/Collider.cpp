#include "RedEngine/Physics/Components/Collider.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"

#include <Box2D/b2_circle_shape.h>
#include <Box2D/b2_edge_shape.h>
#include <Box2D/b2_fixture.h>
#include <Box2D/b2_polygon_shape.h>
#include <algorithm>

namespace red
{
ColliderList::ColliderList(Entity* entity) : Component(entity), m_attachedPhysicBody(nullptr) {}

int ColliderList::AddCollider(Collider&& collider, const ColliderDesc& desc)
{
    collider.m_entity = m_owner;
    collider.m_list = this;

    collider.m_fixtureDef.isSensor = desc.isTrigger;
    collider.m_fixtureDef.restitution = desc.restitution;
    collider.m_fixtureDef.friction = desc.friction;
    collider.m_fixtureDef.density = 1.0f;

    auto insertionResult = m_colliders.insert({m_nextIndex++, std::move(collider)});

    // Set the used data to the right collider
    auto& mapPair = insertionResult.first;
    auto& colliderInserted = mapPair->second;

    b2FixtureUserData userData;
    userData.pointer = (uintptr_t) &colliderInserted;
    colliderInserted.m_fixtureDef.userData = userData;

    m_status = ComponentStatus::DIRTY;

    return mapPair->first;
}

int ColliderList::AddCircleCollider(const CircleColliderDesc& desc)
{
    Collider collider;

    b2CircleShape shape;
    shape.m_p.Set(desc.center.x, desc.center.y);
    shape.m_radius = desc.radius;

    collider.m_shape = std::make_unique<b2CircleShape>(shape);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = collider.m_shape.get();

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int ColliderList::AddEdgeCollider(const EdgeColliderDesc& desc)
{
    Collider collider;

    b2EdgeShape shape;
    shape.SetTwoSided(ConvertToPhysicsVector(desc.start), ConvertToPhysicsVector(desc.end));

    collider.m_shape = std::make_unique<b2EdgeShape>(shape);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = collider.m_shape.get();

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int ColliderList::AddPolygonCollider(const PolygonColliderDesc& desc)
{
    Collider collider;

    b2PolygonShape shape;
    std::vector<b2Vec2> b2Points;
    b2Points.resize(desc.points.size());
    std::transform(desc.points.begin(), desc.points.end(), b2Points.begin(),
                   [](Vector2 v) -> b2Vec2 { return ConvertToPhysicsVector(v); });

    shape.Set(b2Points.data(), static_cast<int32>(b2Points.size()));

    collider.m_shape = std::make_unique<b2PolygonShape>(shape);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = collider.m_shape.get();

    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

void ColliderList::RemoveCollider(int id)
{
    auto it = m_colliders.find(id);

    m_colliders.erase(it);

    m_status = ComponentStatus::DIRTY;
}

red::PhysicBody* ColliderList::GetAttachedPhysicBody() { return m_attachedPhysicBody; }

std::map<int, red::Collider>& ColliderList::GetColliders() { return m_colliders; }

}  // namespace red