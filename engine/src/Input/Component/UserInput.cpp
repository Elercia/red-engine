#include "RedEngine/Input/Component/UserInput.hpp"

#include "RedEngine/Input/InputModule.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(UserInputComponent)

UserInputComponent::UserInputComponent(Entity* entity) : Component(entity)
{
}

UserInputComponent::~UserInputComponent() = default;

[[nodiscard]] bool UserInputComponent::GetKeyDown(const ActionKey& keyId) const
{
    return m_state.at(keyId).isDown;
}

[[nodiscard]] bool UserInputComponent::GetKeyUp(const ActionKey& keyId) const
{
    return m_state.at(keyId).isUp;
}

[[nodiscard]] bool UserInputComponent::GetKey(const ActionKey& keyId) const
{
    return m_state.at(keyId).isPressed;
}  // TODO find and return false if not found

Vector2 UserInputComponent::GetAxis(const AxisKey& /*axisId*/) const
{
    return Vector2();
    // TODO manage axis
}

UserActionMapping UserInputComponent::GetActionMapping()
{
    return m_actionMapping;
}

void UserInputComponent::SetActionMapping(UserActionMapping mapping)
{
    m_actionMapping = std::move(mapping);
}
}  // namespace red