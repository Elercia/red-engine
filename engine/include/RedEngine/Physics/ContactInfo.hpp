#pragma once

#include "RedEngine/Math/Vector.hpp"

#include <vector>

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
    PhysicBody* firstPhysicBody;
    PhysicBody* secondPhysicBody;

    Collider* firstCollider;
    Collider* secondCollider;

    float restitution;
    float tangentSpeed;

    Vector2 normal;

    std::vector<ContactPoint> contactPoints;

    void SwapFirstSecond();
};

struct TriggerInfo
{
    PhysicBody* firstPhysicBody;
    PhysicBody* secondPhysicBody;

    Collider* firstCollider;
    Collider* secondCollider;

    void SwapFirstSecond();
};

}  // namespace red