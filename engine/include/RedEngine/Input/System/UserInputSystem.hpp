#pragma once

#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"

namespace red
{
class UserInputSystem : public System<SinglQuery<QueryRO<EventsComponent>>, SinglQuery<QueryRW<UserInputComponent>>>
{
public:
    UserInputSystem(World* world);
    ~UserInputSystem() = default;

    void Init() override;
    void Finalize() override;

    void Update() override;

private:
    KeyState AglomerateKeyStates(const KeyState& oldState, const Array<KeyState>& states);

    UserInputComponent* m_inputComponent;
};
}  // namespace red