#pragma once
#include "RedEngine/ecs/Component.hpp"

namespace red
{
class RigidBody : public Component
{
public:
    RED_COMPONENT('RIGB')
    RigidBody(Entity* entity) : Component(entity) {}
};
}  // namespace red
