#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/RedEngineBase.hpp"

namespace red
{
class UserInputSystem : public System
{
public:
    UserInputSystem(World* world);
    ~UserInputSystem() = default;

    void Init() override;
    void PreUpdate() override;

private:
    KeyState AglomerateKeyStates(const KeyState& oldState, const std::vector<KeyState>& states);

    UserInputComponent* m_inputComponent;
};
}  // namespace red