#pragma once

#include <vector>

namespace red
{
class PhysicBody;
struct Collider;

struct CollisionInfo
{
    PhysicBody* firstPhysicBody;
    PhysicBody* secondPhysicBody;

    Collider* firstCollider;
    Collider* secondCollider;

    float restitution;
    float tangentSpeed;

    std::vector<int> contactPoints;

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