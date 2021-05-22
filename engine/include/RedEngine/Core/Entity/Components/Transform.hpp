#pragma once

#include "Component.hpp"

#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"

namespace red
{
class Transform : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(Transform, Component)
    RED_END_COMPONENT_REGISTER()

    Transform(Entity* entity, float x, float y);
    Transform(Entity* entity, Vector2 position);
    ~Transform() override = default;

    void Serialize(ILevelComponentData* levelComponentData) const override;
    void Deserialize(const ILevelComponentData* levelComponentData) override;

    [[nodiscard]] const Vector2& GetPosition() const;
    [[nodiscard]] Vector2& GetPosition();

    void SetPosition(const Vector2& pos);
    void SetPosition(float x, float y);

private:
    Vector2 m_position{0, 0};
};
}  // namespace red