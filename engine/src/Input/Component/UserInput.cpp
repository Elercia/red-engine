#include "RedEngine/Input/Component/UserInput.hpp"

namespace red
{
UserInputComponent::UserInputComponent(Entity* entity) : Component(entity) {}

UserInputComponent::~UserInputComponent() = default;

bool UserInputComponent::GetKeyDown(ActionKey keyId) const { return m_state.at(keyId).isDown; }

bool UserInputComponent::GetKeyUp(ActionKey keyId) const { return m_state.at(keyId).isUp; }

bool UserInputComponent::GetKey(ActionKey keyId) const { return m_state.at(keyId).isPressed; } // TODO find and return false if not found

Vector2 UserInputComponent::GetAxis(AxisKey axisId) const
{
    return Vector2();
    // TODO manage axis
}

UserActionMapping UserInputComponent::GetActionMapping() { return m_actionMapping; }

void UserInputComponent::SetActionMapping(UserActionMapping mapping) { m_actionMapping = std::move(mapping); }
}  // namespace red