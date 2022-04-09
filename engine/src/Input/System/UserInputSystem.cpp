#include "RedEngine/Input/System/UserInputSystem.hpp"

#include "RedEngine/Input/InputModule.hpp"

#include "RedEngine/Core/Configuration/IniReader.hpp"
#include "RedEngine/Core/Configuration/UserInputHelper.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"

#include <SDL2/SDL.h>

namespace red
{
UserInputSystem::UserInputSystem(World* world) : System(world), m_inputComponent{nullptr}
{
    m_priority = 1;
}

void UserInputSystem::Init()
{
    System::Init();

    PROFILER_EVENT_CATEGORY("Input Init", ProfilerCategory::Input);

    // TODO move this to the event system
    // TODO add a call to SDL_QuitSubSystem to clean memory (or make sure SDL_Quit is called in every cases)
    SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);

    m_inputComponent = m_world->CreateWorldEntity("UserInputSystemEntity")->AddComponent<UserInputComponent>();

    m_inputComponent->m_actionMapping = utils::UserInputHelper::LoadActionMapping();

    for (auto& mapping : m_inputComponent->m_actionMapping)
    {
        RED_LOG_INFO("Loaded mapping {}", mapping.first);
    }
}

void UserInputSystem::Finalise()
{
    SDL_QuitSubSystem(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
}

void UserInputSystem::PreUpdate()
{
    PROFILER_EVENT_CATEGORY("Input update", ProfilerCategory::Input);

    auto* eventsSystem = m_world->GetWorldComponent<EventsComponent>();
    for (auto& actionMapping : m_inputComponent->m_actionMapping)
    {
        const auto& actionName = actionMapping.first;
        const auto& mapping = actionMapping.second;

        KeyState oldState = m_inputComponent->m_state[actionName];
        KeyState mappingState = eventsSystem->GetKeyState(mapping.mapping);

        Array<KeyState> states;

        for (size_t i = 0; i < g_modifierKeys.size(); i++)
        {
            if (mapping.modifiers.test(i))
            {
                states.push_back(eventsSystem->GetKeyState(g_modifierKeys[i].keyCode));
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

KeyState UserInputSystem::AglomerateKeyStates(const KeyState& oldState, const Array<KeyState>& states)
{
    KeyState resultState = {false, false, false};
    resultState.isPressed = states[0].isPressed;

    for (const auto& state : states)
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
