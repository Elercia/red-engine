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
ColliderList::ColliderList(Entity* entity) : Component(entity)
{
    Entity* physicBodyEntity = entity;

    while (physicBodyEntity)
    {
        m_attachedPhysicBody = physicBodyEntity->GetComponent<PhysicBody>();

        if (m_attachedPhysicBody != nullptr)
        {
            m_attachedPhysicBody->AddCollider(this);
            break;
        }

        physicBodyEntity = physicBodyEntity->GetParent();
    }

    if (m_attachedPhysicBody == nullptr)
        RED_LOG_WARNING("Couldnt attach colliderList to a physicBody");
}

int ColliderList::AddCollider(Collider&& collider, const ColliderDesc& desc)
{
    collider.m_entity = m_owner;
    collider.m_list = this;

    collider.m_fixtureDef.isSensor = desc.isTrigger;
    collider.m_fixtureDef.userData = &collider;

    auto itPair = m_colliders.insert({m_nextIndex++, collider});

    OnColliderAdded(&itPair.first->second);

    return itPair.first->first;
}

int ColliderList::AddCircleCollider(const CircleColliderDesc& desc)
{
    b2CircleShape shape;
    shape.m_p.Set(desc.center.x, desc.center.y);
    shape.m_radius = desc.radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    Collider collider;
    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int ColliderList::AddEdgeCollider(const EdgeColliderDesc& desc)
{
    b2EdgeShape shape;
    shape.Set(desc.start, desc.end);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    Collider collider;
    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

int ColliderList::AddPolygonCollider(const PolygonColliderDesc& desc)
{
    b2PolygonShape shape;
    std::vector<b2Vec2> b2Points;
    b2Points.resize(desc.points.size());
    std::transform(desc.points.begin(), desc.points.end(), b2Points.begin(),
                   [](Vector2 v) -> b2Vec2 { return v; });

    shape.Set(b2Points.data(), static_cast<int32>(b2Points.size()));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;

    Collider collider;
    collider.m_fixtureDef = fixtureDef;

    return AddCollider(std::move(collider), desc);
}

void ColliderList::RemoveCollider(int id)
{
    auto it = m_colliders.find(id);

    OnColliderRemoved(&it->second);

    m_colliders.erase(it);
}

red::PhysicBody* ColliderList::GetAttachedPhysicBody() const { return m_attachedPhysicBody; }

}  // namespace red