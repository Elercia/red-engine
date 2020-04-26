#pragma once

#include <RedEngine/Math/Vector.hpp>
#include "Component.hpp"

namespace red
{
class Transform : public Component
{
    RED_COMPONENT("TRANSFORM")
public:
    Transform(Entity* entity, int x, int y);
    Transform(Entity* entity, Vector2 position);
    ~Transform() override = default;

    [[nodiscard]] Vector2 GetPosition() const;

private:
    Vector2 m_position{0, 0};
};
}  // namespace red