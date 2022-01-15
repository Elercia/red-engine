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
    RED_MEMBER("position", m_position, "The local position of the entity", 0);
    RED_MEMBER("scale", m_scale, "The local scale of the entity", 0);
    RED_MEMBER("rotation", m_rotation, "The local rotation of the entity", 0);
    RED_END_COMPONENT_REGISTER()

    Transform(Entity* entity);
    Transform(Entity* entity, float x, float y);
    Transform(Entity* entity, Vector2 position);
    virtual ~Transform() = default;

    [[nodiscard]] const Vector2& GetPosition() const;
    [[nodiscard]] Vector2& GetPosition();

    [[nodiscard]] const Vector2& GetScale() const;
    [[nodiscard]] Vector2& GetScale();

    [[nodiscard]] float GetRotationDeg() const;
    [[nodiscard]] float GetRotationRad() const;

    void SetPosition(const Vector2& pos);
    void SetPosition(float x, float y);
    void SetScale(const Vector2& scale);
    void SetRotationDeg(float rotationDeg);
    void SetRotationRad(float rotationRad);
    void SetDepth(float depth);

    void UpdateWorldMatrixIfNeeded();
    const Matrix44& GetWorldMatrix() const;
    Matrix44& GetWorldMatrix();

private:
    // World position
    Vector2 m_position{0.f, 0.f};
    Vector2 m_scale{1.f, 1.f};
    float m_rotation{0.f};  // degrees
    Vector2 m_roationAnchor{0.f, 0.f};

    float m_depth{0.f};

    Matrix44 m_worldMatrix;
    bool m_dirtyWorldMatrix{true};
};
}  // namespace red