#pragma once

#include "Component.hpp"

#include "RedEngine/RedEngineBase.hpp"

namespace red
{
class RigidBody : public Component
{
public:
    RigidBody(Entity* entity) : Component(entity) {}
};
}  // namespace red
