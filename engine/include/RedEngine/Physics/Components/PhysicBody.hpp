#pragma once

#include "RedEngine//Math/Vector.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Physics/ContactInfo.hpp"

#include <box2d/b2_body.h>
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
    float linearDamping{0.f};
    float angularDamping{0.f};
    float gravityScale{1.f};
};

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(PhysicBody)

class PhysicBody : public Component
{
    friend class PhysicSystem;
    friend class PhysicsWorld;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(PhysicBody, Component)
    RED_END_COMPONENT_REGISTER()

    using OnCollisionSignalType = Signal<const CollisionInfo&>;
    using OnTriggerSignalType = Signal<const TriggerInfo&>;

    PhysicBody(Entity* entity);
    PhysicBody(Entity* entity, const PhysicBodyCreationDesc& desc);
    ~PhysicBody();

    void ApplyForce(const Vector2& force, const Vector2& relativePosition);

    b2Body* GetBody();
    void SetBody(b2Body* body);

    OnTriggerSignalType m_triggerSignal;
    OnCollisionSignalType m_collisionSignal;

private:
    PhysicBodyCreationDesc m_desc;
    b2Body* m_body;

    std::vector<OnCollisionSignalType::Slot> m_collisionSlots;

    std::vector<OnTriggerSignalType::Slot> m_triggerSlots;
};
}  // namespace red