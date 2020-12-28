#pragma once

#include "RedEngine//Math/Vector.hpp"
#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <Box2D/Dynamics/b2Body.h>
#include <vector>

namespace red
{
class ColliderList;
struct Collider;

enum class PhysicsBodyType
{
    STATIC_BODY,
    DYNAMIC_BODY,
    KINEMATIC_BODY
};

struct PhysicBodyCreationDesc
{
    PhysicsBodyType type{PhysicsBodyType::STATIC_BODY};
    float32 linearDamping{0.f};
    float32 angularDamping{0.f};
    float32 gravityScale{1.f};
};

class PhysicBody : public Component
{
    friend class PhysicSystem;
    friend class PhysicsWorld;

    using OnCollisionSignalType = Signal<const CollisionInfo&>;
    using OnTriggerSignalType = Signal<const TriggerInfo&>;

public:
    PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc);
    ~PhysicBody();

    void ApplyForce(const Vector2& force, const Vector2& relativePosition);

    b2Body* GetBody();

    OnTriggerSignalType m_triggerSignal;
    OnCollisionSignalType m_collisionSignal;

private:
    PhysicBodyCreationDesc m_desc;
    b2Body* m_body;

    std::vector<OnCollisionSignalType::Slot> m_collisionSlots;

    std::vector<OnTriggerSignalType::Slot> m_triggerSlots;
};
}  // namespace red