#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"

namespace red
{
class UserInputSystem : public System
{
public:
    UserInputSystem(World* world);
    ~UserInputSystem() = default;

    void Init() override;
    void Finalise() override;
    void PreUpdate() override;

private:
    KeyState AglomerateKeyStates(const KeyState& oldState, const Array<KeyState>& states);

    UserInputComponent* m_inputComponent;
};
}  // namespace red