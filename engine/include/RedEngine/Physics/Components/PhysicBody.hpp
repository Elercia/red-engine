#pragma once

#include "RedEngine//Math/Vector.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"

#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace red
{
struct ColliderDesc
{
    bool isTrigger{false};
    float friction{0.f};
    float restitution{1.f};
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
    Array<Vector2> points{};
};

using ColliderId = uint32;

struct Collider
{
    b2FixtureDef m_fixtureDef;
    b2Fixture* m_fixture{nullptr};

    bool IsTrigger() const
    {
        return m_fixtureDef.isSensor;
    }
};

enum class PhysicsBodyType
{
    STATIC_BODY,
    DYNAMIC_BODY,
    KINEMATIC_BODY
};

struct PhysicBodyCreationDesc
{
    PhysicsBodyType type{PhysicsBodyType::STATIC_BODY};
    float linearDamping{0.f};
    float angularDamping{0.f};
    float gravityScale{1.f};
};

// TODO Collision layers
class PhysicBody : public Component
{
    friend class PhysicSystem;
    friend class PhysicsWorld;

public:
    using OnCollisionSignalType = Signal<const CollisionInfo&>;
    using OnTriggerSignalType = Signal<const TriggerInfo&>;

    PhysicBody(Entity* entity);
    PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc);
    ~PhysicBody();

    bool IsStatic() const;

    void ApplyForce(const Vector2& force, const Vector2& relativePosition);

    int AddCircleCollider(const CircleColliderDesc& desc);
    int AddEdgeCollider(const EdgeColliderDesc& desc);
    int AddPolygonCollider(const PolygonColliderDesc& desc);

    void RemoveCollider(int id);

    Map<ColliderId, Collider>& GetColliders();
    const Map<ColliderId, Collider>& GetColliders() const;

    b2Body* GetBody();
    void SetBody(b2Body* body);

    OnTriggerSignalType m_triggerSignal;
    OnCollisionSignalType m_collisionSignal;

    template <typename T>
    friend void RegisterMembers(ComponentTraits& traits);

private:
    int AddCollider(Collider&& collider, const ColliderDesc& desc);

private:
    PhysicBodyCreationDesc m_desc;
    b2Body* m_body;
    Map<ColliderId, Collider> m_colliders;
    ColliderId m_nextColliderIndex;

    Array<OnCollisionSignalType::Slot> m_collisionSlots;
    Array<OnTriggerSignalType::Slot> m_triggerSlots;
};
}  // namespace red