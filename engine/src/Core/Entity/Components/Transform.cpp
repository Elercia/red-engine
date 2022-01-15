#include "RedEngine/Core/Entity/Components/Transform.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Math/Math.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/MatrixFunctions.hpp"
#include "RedEngine/Math/Vector.hpp"

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
    m_dirtyWorldMatrix = true;
}

void Transform::SetPosition(float x, float y)
{
    m_position = Vector2(x, y);
    m_dirtyWorldMatrix = true;
}

const Vector2& Transform::GetScale() const
{
    return m_scale;
}

Vector2& Transform::GetScale()
{
    return m_scale;
}

float Transform::GetRotationDeg() const
{
    return m_rotation;
}

float Transform::GetRotationRad() const
{
    return Math::ToRadians(m_rotation);
}

void Transform::SetScale(const Vector2& scale)
{
    m_scale = scale;
    m_dirtyWorldMatrix = true;
}

void Transform::SetRotationDeg(float rotationDeg)
{
    m_rotation = rotationDeg;
    m_dirtyWorldMatrix = true;
}

void Transform::SetRotationRad(float rotationRad)
{
    m_rotation = Math::ToDegrees(rotationRad);
    m_dirtyWorldMatrix = true;
}

void Transform::SetDepth(float depth)
{
    m_depth = depth;
    m_dirtyWorldMatrix = true;
}

void Transform::UpdateWorldMatrixIfNeeded()
{
    if (m_dirtyWorldMatrix)
    {
        m_dirtyWorldMatrix = false;

        m_worldMatrix = Matrix44::Identity();
        m_worldMatrix = Math::Translate(m_worldMatrix, Vector3(m_position, m_depth));

        m_worldMatrix = Math::Translate(m_worldMatrix, Vector3(m_roationAnchor, 0.0f));
        m_worldMatrix = Math::Rotate(m_worldMatrix, Vector3(0.0f, 0.0f, Math::ToRadians(m_rotation)));
        m_worldMatrix = Math::Translate(m_worldMatrix, -Vector3(m_roationAnchor, 0.0f));
        m_worldMatrix = Math::Scale(m_worldMatrix, Vector3(m_scale, 1.0f));
    }
}

const Matrix44& Transform::GetWorldMatrix() const
{
    return m_worldMatrix;
}

Matrix44& Transform::GetWorldMatrix()
{
    UpdateWorldMatrixIfNeeded();

    return m_worldMatrix;
}

}  // namespace red