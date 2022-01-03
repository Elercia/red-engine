#include "RedEngine/Physics/ContactInfo.hpp"

#include "RedEngine/Physics/PhysicsModule.hpp"

#include <algorithm>

namespace red
{
void CollisionInfo::SwapFirstSecond()
{
    std::swap(firstPhysicBody, secondPhysicBody);
    std::swap(firstCollider, secondCollider);
}

void TriggerInfo::SwapFirstSecond()
{
    std::swap(firstPhysicBody, secondPhysicBody);
    std::swap(firstCollider, secondCollider);
}
}  // namespace red