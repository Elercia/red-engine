#include "RedEngine/Core/Entity/Components/Transform.hpp"

#include "RedEngine/Level/LevelData.hpp"

namespace red
{
Transform::Transform(Entity* entity, float x, float y) : Transform(entity, {x, y})
{
}

Transform::Transform(Entity* entity, Vector2 position) : Component(entity), m_position(position)
{
}

void Transform::Serialize(ILevelComponentData* levelComponentData) const
{
    Component::Serialize(levelComponentData);

    levelComponentData->WriteVector2("position", m_position);
}

void Transform::Deserialize(const ILevelComponentData* levelComponentData)
{
    Component::Deserialize(levelComponentData);

    m_position = levelComponentData->ReadVector2("position");
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