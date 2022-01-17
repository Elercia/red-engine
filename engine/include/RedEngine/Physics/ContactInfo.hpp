#pragma once

#include "RedEngine/Math/Vector.hpp"

#include "RedEngine/Core/Container/Array.hpp"

namespace red
{
class PhysicBody;
struct Collider;

struct ContactPoint
{
    Vector2 localPoint{0.f, 0.f};
    float normalImpulse{0.f};
    float tangentImpulse{0.f};
};

struct CollisionInfo
{
    PhysicBody* firstPhysicBody{nullptr};
    PhysicBody* secondPhysicBody{nullptr};

    Collider* firstCollider{nullptr};
    Collider* secondCollider{nullptr};

    float restitution{0.f};
    float tangentSpeed{0.f};

    Vector2 normal{0.f, 0.f};

    Array<ContactPoint> contactPoints{};

    void SwapFirstSecond();
};

struct TriggerInfo
{
    PhysicBody* firstPhysicBody{nullptr};
    PhysicBody* secondPhysicBody{nullptr};

    Collider* firstCollider{nullptr};
    Collider* secondCollider{nullptr};

    void SwapFirstSecond();
};

}  // namespace red