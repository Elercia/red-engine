#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/Input/UserInputDefinition.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <map>

namespace red
{
// TODO handle joysticks and gamepads in general
class UserInputComponent : public Component
{
    friend class UserInputSystem;

public:
    explicit UserInputComponent(Entity* entity);
    ~UserInputComponent() override;

    [[nodiscard]] bool GetKeyDown(ActionKey keyId) const;
    [[nodiscard]] bool GetKeyUp(ActionKey keyId) const;
    [[nodiscard]] bool GetKey(ActionKey keyId) const;

    [[nodiscard]] Vector2 GetAxis(AxisKey axisId) const;

    [[nodiscard]] UserActionMapping GetActionMapping();
    void SetActionMapping(UserActionMapping mapping);

private:
    UserActionMapping m_actionMapping{};
    UserActionState m_state{};
};

}  // namespace red
