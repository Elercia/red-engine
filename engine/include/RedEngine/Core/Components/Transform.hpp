#pragma once

#include <RedEngine/Math/Vector.hpp>
#include "Component.hpp"

namespace red
{
class Transform : public Component
{
public:
    Transform(Entity* entity, float x, float y);
    Transform(Entity* entity, Vector2 position);
    ~Transform() override = default;

    [[nodiscard]] const Vector2& GetPosition() const;
    [[nodiscard]] Vector2& GetPosition();

private:
    Vector2 m_position{0, 0};
};
}  // namespace red