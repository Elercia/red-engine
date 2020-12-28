#include "RedEngine/Input/System/UserInputSystem.hpp"

#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Configuration/UserInputHelper.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"

namespace red
{
UserInputSystem::UserInputSystem(World* world) : System(world) {}

void UserInputSystem::Init()
{
    PROFILER_CATEGORY("Input Init", Optick::Category::Input);

    auto* singeltonEntity = GetSingletonEntity();

    m_inputComponent = singeltonEntity->GetComponent<UserInputComponent>();

    m_inputComponent->m_actionMapping = utils::UserInputHelper::LoadActionMapping();

    for (auto& mapping : m_inputComponent->m_actionMapping)
    {
        RED_LOG_INFO("Loaded mapping {}", mapping.first);
    }
}

void UserInputSystem::PreUpdate()
{
    PROFILER_CATEGORY("Input Update", Optick::Category::Input);

    EventSystem* manager = GetSubEngine<EventSystem>();
    for (auto& actionMapping : m_inputComponent->m_actionMapping)
    {
        auto& actionName = actionMapping.first;
        auto& mapping = actionMapping.second;

        KeyState oldState = m_inputComponent->m_state[actionName];
        KeyState mappingState = manager->GetKeyState(mapping.mapping);

        std::vector<KeyState> states;

        for (size_t i = 0; i < g_modifierKeys.size(); i++)
        {
            if (mapping.modifiers.test(i))
            {
                states.push_back(manager->GetKeyState(g_modifierKeys[i].keyCode));
            }
        }

        // Push the mapping
        states.push_back(mappingState);

        auto resultState = AglomerateKeyStates(oldState, states);

        m_inputComponent->m_state[actionName] = resultState;

        if (resultState.isDown)
        {
            RED_LOG_DEBUG("User action {} is down", actionName);
        }

        if (resultState.isUp)
        {
            RED_LOG_DEBUG("User action {} is up", actionName);
        }
    }
}

red::KeyState UserInputSystem::AglomerateKeyStates(const KeyState& oldState, const std::vector<KeyState>& states)
{
    KeyState resultState = {false, false, false};
    resultState.isPressed = states[0].isPressed;

    for (auto& state : states)
    {
        // A user input is pressed only if all the required keys are pressed
        resultState.isPressed = state.isPressed && resultState.isPressed;
    }

    if (!oldState.isPressed && resultState.isPressed)
        resultState.isDown = true;

    if (oldState.isPressed && !resultState.isPressed)
        resultState.isUp = true;

    return resultState;
}

}  // namespace red
