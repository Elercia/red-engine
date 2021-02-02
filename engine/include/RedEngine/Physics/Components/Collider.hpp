#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <Box2D/b2_shape.h>
#include <Box2D/b2_fixture.h>
#include <map>
#include <memory>

namespace red
{
class PhysicBody;
class ColliderList;
struct Collider;

struct ColliderDesc
{
    bool isTrigger{false};
    float friction{0.f};
    float restitution{0.f};
};

struct CircleColliderDesc : public ColliderDesc
{
    Vector2 center{0.f, 0.f};
    float radius{0.1f};
};

struct EdgeColliderDesc : public ColliderDesc
{
    Vector2 start{0.f, 0.f};
    Vector2 end{0.f, 0.f};
};

struct PolygonColliderDesc : public ColliderDesc
{
    std::vector<Vector2> points{};
};

struct Collider
{
    Entity* m_entity;
    ColliderList* m_list;
    b2FixtureDef m_fixtureDef;
    b2Fixture* m_fixture;
    std::unique_ptr<b2Shape> m_shape{nullptr};

    bool IsTrigger() { return m_fixtureDef.isSensor; }
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