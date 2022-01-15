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

Transform::Transform(Entity* entity, Vector2 position) : Component(entity), m_localPosition(position)
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
    Transform* parentTransform =  parent != nullptr ? parent->GetComponent<Transform>() : nullptr;
    bool parentDirty = parentTransform != nullptr ? parentTransform->m_dirtyWorldMatrix : false;

    if (m_dirtyWorldMatrix || parentDirty) 
    {
        m_dirtyWorldMatrix = false;

        m_worldMatrix = Matrix44::Identity();
        m_worldMatrix = Math::Translate(m_worldMatrix, Vector3(m_localPosition, m_localDepth));

        m_worldMatrix = Math::Translate(m_worldMatrix, Vector3(m_localRotationAnchor, 0.0f));
        m_worldMatrix = Math::Rotate(m_worldMatrix, Vector3(0.0f, 0.0f, Math::ToRadians(m_localRotation)));
        m_worldMatrix = Math::Translate(m_worldMatrix, -Vector3(m_localRotationAnchor, 0.0f));
        m_worldMatrix = Math::Scale(m_worldMatrix, Vector3(m_localScale, 1.0f));

        if ( parentTransform != nullptr)
        {
            parentTransform->UpdateWorldMatrixIfNeeded();
            m_worldMatrix = parentTransform->GetLocalWorldMatrix() * m_worldMatrix;
        }
        else
        {
            m_worldMatrix = m_localWorldMatrix;
        }
    }
}

const Matrix44& Transform::GetLocalWorldMatrix() const
{
    return m_worldMatrix;
}

Matrix44& Transform::GetLocalWorldMatrix()
{
    UpdateWorldMatrixIfNeeded();

    return m_worldMatrix;
}

}  // namespace red