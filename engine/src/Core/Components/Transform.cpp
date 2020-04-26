#include "RedEngine/Core/Components/Transform.hpp"

namespace red
{
Transform::Transform(Entity* entity, int x, int y) : Transform(entity, {x, y}) {}
Transform::Transform(Entity* entity, Vector2 position) : Component(entity), m_position(position) {}

Vector2 Transform::GetPosition() const { return m_position; }

}  // namespace red