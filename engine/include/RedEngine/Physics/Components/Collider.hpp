#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <Box2D/Collision/Shapes/b2Shape.h>
#include <Box2D/Dynamics/b2Fixture.h>

#include <map>
#include <memory>


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
    std::unique_ptr<b2Shape> m_shape{nullptr};
};

// TODO Collision layers
class ColliderList : public Component
{
    friend class PhysicSystem;

public:
    ColliderList(Entity* entity);
    ~ColliderList() = default;

    int AddCircleCollider(const CircleColliderDesc& desc);
    int AddEdgeCollider(const EdgeColliderDesc& desc);
    int AddPolygonCollider(const PolygonColliderDesc& desc);
    
    void RemoveCollider(int id);

    PhysicBody* GetAttachedPhysicBody();

    std::map<int, Collider>& GetColliders();

private:
    int AddCollider(Collider&& collider, const ColliderDesc& desc);

    std::map<int, Collider> m_colliders;
    int m_nextIndex{0};
    PhysicBody* m_attachedPhysicBody;
};

}  // namespace red