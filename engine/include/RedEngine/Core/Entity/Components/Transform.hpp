#pragma once

#include "Component.hpp"

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"

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
    ~Transform() override = default;

    [[nodiscard]] const Vector2& GetPosition() const;
    [[nodiscard]] Vector2& GetPosition();

    void SetPosition(const Vector2& pos);
    void SetPosition(float x, float y);

private:
    Vector2 m_position{0.f, 0.f};
    float m_rotation{0.f};
    Vector2 m_scale{0.f, 0.f};
};
}  // namespace red