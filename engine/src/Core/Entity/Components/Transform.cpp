#include "RedEngine/Core/Entity/Components/Transform.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Transform)

Transform::Transform(Entity* entity) : Transform(entity, {0.f, 0.f})
{
}

Transform::Transform(Entity* entity, float x, float y) : Transform(entity, {x, y})
{
}

Transform::Transform(Entity* entity, Vector2 position) : Component(entity), m_position(position)
{
}

const Vector2& Transform::GetPosition() const
{
    return m_position;
}

Vector2& Transform::GetPosition()
{
    return m_position;
}

void Transform::SetPosition(const Vector2& pos)
{
    m_position = pos;
}

void Transform::SetPosition(float x, float y)
{
    m_position = Vector2(x, y);
}

}  // namespace red