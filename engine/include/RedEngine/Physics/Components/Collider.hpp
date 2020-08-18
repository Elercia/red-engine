#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <Box2D/Dynamics/b2Fixture.h>

#include <map>

namespace red
{
class PhysicBody;
class ColliderList;
struct Collider;

struct ColliderDesc
{
    bool isTrigger;
};

struct CircleColliderDesc : public ColliderDesc
{
    Vector2 center;
    float radius;
};

struct EdgeColliderDesc : public ColliderDesc
{
    Vector2 start;
    Vector2 end;
};

struct PolygonColliderDesc : public ColliderDesc
{
    std::vector<Vector2> points;
};

struct Collider
{
    Entity* m_entity;
    ColliderList* m_list;
    b2FixtureDef m_fixtureDef;
    b2Fixture* m_fixture;
};

// TODO Collision layers
class ColliderList : public Component
{
public:
    ColliderList(Entity* entity);
    ~ColliderList() = default;

    int AddCircleCollider(const CircleColliderDesc& desc);
    int AddEdgeCollider(const EdgeColliderDesc& desc);
    int AddPolygonCollider(const PolygonColliderDesc& desc);
    
    void RemoveCollider(int id);

    Signal<Collider*> OnColliderAdded;
    Signal<Collider*> OnColliderRemoved;

    PhysicBody* GetAttachedPhysicBody() const;

private:
    int AddCollider(Collider&& collider, const ColliderDesc& desc);

    std::map<int, Collider> m_colliders;
    int m_nextIndex{0};
    PhysicBody* m_attachedPhysicBody;
};

}  // namespace red