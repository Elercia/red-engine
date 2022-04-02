#include "RedEngine/Core/Entity/Components/Transform.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
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

Transform::Transform(Entity* entity, Vector2 position)
    : Component(entity), m_localPosition(position), m_dirtyWorldMatrix(true)
{
}

const Vector2& Transform::GetPosition() const
{
    return m_localPosition;
}

Vector2& Transform::GetPosition()
{
    return m_localPosition;
}

void Transform::SetPosition(const Vector2& pos)
{
    m_localPosition = pos;
    m_dirtyWorldMatrix = true;
}

void Transform::SetPosition(float x, float y)
{
    m_localPosition = Vector2(x, y);
    m_dirtyWorldMatrix = true;
}

const Vector2& Transform::GetScale() const
{
    return m_localScale;
}

Vector2& Transform::GetScale()
{
    return m_localScale;
}

float Transform::GetDepth() const
{
    auto* parent = GetOwner()->GetParent();
    Transform* parentTransform = parent != nullptr ? parent->GetComponent<Transform>() : nullptr;

    return parentTransform != nullptr ? m_localDepth + parentTransform->GetDepth() : m_localDepth;
}

float Transform::GetRotationDeg() const
{
    return m_localRotation;
}

float Transform::GetRotationRad() const
{
    return Math::ToRadians(m_localRotation);
}

void Transform::SetScale(const Vector2& scale)
{
    m_localScale = scale;
    m_dirtyWorldMatrix = true;
}

void Transform::SetRotationDeg(float rotationDeg)
{
    m_localRotation = rotationDeg;
    m_dirtyWorldMatrix = true;
}

void Transform::SetRotationRad(float rotationRad)
{
    m_localRotation = Math::ToDegrees(rotationRad);
    m_dirtyWorldMatrix = true;
}

void Transform::SetDepth(float depth)
{
    m_localDepth = depth;
    m_dirtyWorldMatrix = true;
}

void Transform::UpdateWorldMatrixIfNeeded()
{
    auto* parent = GetOwner()->GetParent();
    Transform* parentTransform = parent != nullptr ? parent->GetComponent<Transform>() : nullptr;
    bool parentDirty = parentTransform != nullptr ? parentTransform->m_dirtyWorldMatrix : false;

    if (m_dirtyWorldMatrix)
    {
        m_localWorldMatrix = Math::Translate(Matrix44::Identity(), Vector3(m_localPosition, m_localDepth));

        m_localWorldMatrix = Math::Translate(m_localWorldMatrix, Vector3(m_localRotationAnchor, 0.0f));
        m_localWorldMatrix = Math::Rotate(m_localWorldMatrix, Vector3(0.0f, 0.0f, Math::ToRadians(m_localRotation)));
        m_localWorldMatrix = Math::Translate(m_localWorldMatrix, -Vector3(m_localRotationAnchor, 0.0f));
        m_localWorldMatrix = Math::Scale(m_localWorldMatrix, Vector3(m_localScale, 1.0f));
    }

    if ((m_dirtyWorldMatrix || parentDirty) && parentTransform != nullptr)
    {
        parentTransform->UpdateWorldMatrixIfNeeded();
        m_worldMatrix = parentTransform->GetWorldMatrix() * m_localWorldMatrix;
    }
    else
    {
        m_worldMatrix = m_localWorldMatrix;
    }

    m_dirtyWorldMatrix = false;
}

const Matrix44& Transform::GetLocalWorldMatrix() const
{
    return m_localWorldMatrix;
}

Matrix44& Transform::GetLocalWorldMatrix()
{
    UpdateWorldMatrixIfNeeded();

    return m_localWorldMatrix;
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