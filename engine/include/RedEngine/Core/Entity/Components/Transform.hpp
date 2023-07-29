#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Math/Matrix.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
class Transform : public Component
{
public:
    Transform(Entity* entity);
    Transform(Entity* entity, float x, float y);
    Transform(Entity* entity, Vector2 position);
    ~Transform() = default;

    [[nodiscard]] const Vector2& GetLocalPosition() const;  // TODO rename to GetLocalPosition
    [[nodiscard]] Vector2& GetLocalPosition();              // TODO Add GetWorldPosisition

    [[nodiscard]] const Vector2& GetScale() const;
    [[nodiscard]] Vector2& GetScale();

    [[nodiscard]] float GetLocalRotationDeg() const;
    [[nodiscard]] float GetLocalRotationRad() const;

    void SetLocalPosition(const Vector2& pos);
    void SetLocalPosition(float x, float y);
    void SetScale(const Vector2& scale);
    void SetLocalRotationDeg(float rotationDeg);
    void SetLocalRotationRad(float rotationRad);

    void UpdateWorldMatrixIfNeeded();

    const Matrix33& GetLocalWorldMatrix() const;
    Matrix33& GetLocalWorldMatrix();
    const Matrix33& GetWorldMatrix() const;
    Matrix33& GetWorldMatrix();

    void SetLocked(bool locked);

    template <typename T>
    friend void RegisterMembers(ComponentTraits& traits);

private:
    // World position
    Vector2 m_localPosition{0.f, 0.f};
    Vector2 m_localScale{1.f, 1.f};
    float m_localRotation{0.f};  // degrees
    Vector2 m_localRotationAnchor{0.f, 0.f};

    bool m_locked{false};

    Matrix33 m_localWorldMatrix;
    Matrix33 m_worldMatrix;  // include parent transforms
    bool m_dirtyWorldMatrix{true};
};
}  // namespace red