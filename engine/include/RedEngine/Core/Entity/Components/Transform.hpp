#pragma once

#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"

#include "Component.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(Transform)

class Transform : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(Transform, Component)
    RED_MEMBER("position", m_localPosition, "The local position of the entity", 0);
    RED_MEMBER("scale", m_localScale, "The local scale of the entity", 0);
    RED_MEMBER("rotation", m_localRotation, "The local rotation of the entity", 0);
    RED_MEMBER("rotationAnchor", m_localRotationAnchor, "The local rotation anchor ", 0);
    //RED_MEMBER("depth", m_localDepth, "The local rotation of the entity", 0);
    RED_END_COMPONENT_REGISTER()

    Transform(Entity* entity);
    Transform(Entity* entity, float x, float y);
    Transform(Entity* entity, Vector2 position);
    virtual ~Transform() = default;

    [[nodiscard]] const Vector2& GetPosition() const;
    [[nodiscard]] Vector2& GetPosition();

    [[nodiscard]] const Vector2& GetScale() const;
    [[nodiscard]] Vector2& GetScale();

    [[nodiscard]] float GetDepth() const;

    [[nodiscard]] float GetRotationDeg() const;
    [[nodiscard]] float GetRotationRad() const;

    void SetPosition(const Vector2& pos);
    void SetPosition(float x, float y);
    void SetScale(const Vector2& scale);
    void SetRotationDeg(float rotationDeg);
    void SetRotationRad(float rotationRad);
    void SetDepth(float depth);

    void UpdateWorldMatrixIfNeeded();

    const Matrix33& GetLocalWorldMatrix() const;
    Matrix33& GetLocalWorldMatrix();
    const Matrix33& GetWorldMatrix() const;
    Matrix33& GetWorldMatrix();

private:
    // World position
    Vector2 m_localPosition{0.f, 0.f};
    Vector2 m_localScale{1.f, 1.f};
    float m_localRotation{0.f};  // degrees
    Vector2 m_localRotationAnchor{0.f, 0.f};

    //float m_localDepth{0.f};

    Matrix33 m_localWorldMatrix;
    Matrix33 m_worldMatrix; // include parent transforms
    bool m_dirtyWorldMatrix{true};
};
}  // namespace red