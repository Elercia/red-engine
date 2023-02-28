#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/Input/UserInputDefinition.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
// TODO handle joysticks and gamepads in general
class UserInputComponent : public Component
{
    friend class UserInputSystem;

public:
    explicit UserInputComponent(Entity* entity);
    ~UserInputComponent();

    [[nodiscard]] bool GetKeyDown(const ActionKey& keyId) const;
    [[nodiscard]] bool GetKeyUp(const ActionKey& keyId) const;
    [[nodiscard]] bool GetKey(const ActionKey& keyId) const;

    [[nodiscard]] Vector2 GetAxis(const AxisKey& axisId) const;

    [[nodiscard]] UserActionMapping GetActionMapping();
    void SetActionMapping(UserActionMapping mapping);

private:
    UserActionMapping m_actionMapping{};
    UserActionState m_state{};
};

}  // namespace red
