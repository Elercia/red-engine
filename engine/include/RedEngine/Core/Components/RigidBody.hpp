#pragma once
#include "Component.hpp"

namespace red
{
class RigidBody : public Component
{
    RED_COMPONENT("RIGB")

public:
    RigidBody(Entity* entity) : Component(entity) {}
};
}  // namespace red
