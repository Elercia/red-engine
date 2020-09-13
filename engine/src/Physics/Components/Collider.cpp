#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Physics/Components/Collider.hpp>
#include <RedEngine/Physics/Components/PhysicBody.hpp>

#include <Box2D/Dynamics/b2Fixture.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <Box2D/Collision/Shapes/b2CircleShape.h>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

#include <algorithm>

namespace red
{
ColliderList::ColliderList(Entity* entity) : Component(entity), m_attachedPhysicBody(nullptr) {}

int ColliderList::AddCollider(Collider&& collider, const ColliderDesc& desc)
{
    collider.m_entity = m_owner;
    collider.m_list = this;

    collider.m_fixtureDef.isSensor = desc.isTrigger;
    collider.m_fixtureDef.userData = &collider;

    auto itPair = m_colliders.insert({m_nextIndex++, std::move(collider)});

    m_status = ComponentStatus::DIRTY;

    return itPair.first->first;
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
    shape.Set(desc.start, desc.end);

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
                   [](Vector2 v) -> b2Vec2 { return v; });

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