#include "RedEngine/Core/Event/System/EventSystem.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Input/InputDefinitionTranslationUnit.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>

namespace red
{
EventSystem::EventSystem(World* world) : System(world)
{
}

void EventSystem::Init()
{
    System::Init();
    m_world->CreateWorldEntity("EventSystemEntity")->AddComponent<EventsComponent>();

    if (SDL_InitSubSystem(SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
    {
        RED_LOG_ERROR("Failed to init subsystem event");
    }
}

void EventSystem::Update()
{
    PROFILER_EVENT_CATEGORY("EventSystem::PreUpdate", ProfilerCategory::Input);

    EventsComponent* events = m_world->GetWorldComponent<EventsComponent>();

    auto codes = GetKeyCodeReadableDb();
    auto mouseCodes = GetSDLMouseTranslationMap();
    auto keyboardCodes = GetSDLKeyboardTranslationMap();

    // Reset the inputs
    // KeyDown and KeyUp only live for one frame
    for (auto& state : events->m_keyStates)
    {
        state.isDown = false;
        state.isUp = false;
    }

    events->m_windowIdResized.clear();

    // Update the inputs
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
#ifdef RED_DEVBUILD
        if (ImGui::GetCurrentContext() != nullptr)
            ImGui_ImplSDL2_ProcessEvent(&event);
#endif

        /* handle your event here */
        switch (event.type)
        {
            // -------- WINDOW --------
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        events->m_quitRequested = true;
                        RED_LOG_DEBUG("Events : Window event close");
                        break;
                    case SDL_WINDOWEVENT_SIZE_CHANGED:
                        RED_LOG_DEBUG("Events : Window event size changed");
                        events->m_windowIdResized.push_back(event.window.windowID);
                        break;
                }
            }
            break;
                // -------- QUIT --------
            case SDL_QUIT:
                events->m_quitRequested = true;
                RED_LOG_DEBUG("Events : Quit Requested");
                break;
                // -------- KEYS --------
            case SDL_KEYDOWN:
            {
                auto& keyState = events->m_keyStates[keyboardCodes.at(event.key.keysym.scancode)];

                if (!keyState.isPressed)
                {
                    keyState.isPressed = true;
                    keyState.isDown = true;

                    RED_LOG_TRACE("Events : Key DOWN {}", codes[keyboardCodes.at(event.key.keysym.scancode)]);
                }
            }
            break;
            case SDL_KEYUP:
            {
                auto& keyState = events->m_keyStates[keyboardCodes.at(event.key.keysym.scancode)];

                keyState.isPressed = false;
                keyState.isUp = true;

                RED_LOG_TRACE("Events : Key UP {}", codes[keyboardCodes.at(event.key.keysym.scancode)]);
            }
            break;
                // -------- MOUSE --------
            case SDL_MOUSEMOTION:
            {
                events->m_mousePosition = Vector2i{event.motion.x, event.motion.y};
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                auto& keyState = events->m_keyStates[mouseCodes.at(event.button.button)];

                if (!keyState.isDown)
                {
                    keyState = {true, false, true};
                    RED_LOG_TRACE("Mouse button DOWN {}", codes[mouseCodes.at(event.button.button)]);
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                auto& keyState = events->m_keyStates[mouseCodes.at(event.button.button)];

                if (!keyState.isUp)
                {
                    keyState = {false, true, false};
                    RED_LOG_TRACE("Mouse button UP {}", codes[mouseCodes.at(event.button.button)]);
                }
            }
            break;
            case SDL_MOUSEWHEEL:
            {
                RED_LOG_TRACE("Mouse wheel detected delta x:{}, y:{}", event.wheel.x, event.wheel.y);
            }
            break;
                // -------- GAMEPAD --------
            case SDL_CONTROLLERAXISMOTION:
            {
                RED_LOG_TRACE("Gamepad axis motion");
            }
            break;
            case SDL_CONTROLLERBUTTONDOWN:
            {
                RED_LOG_TRACE("Gamepad button down");
            }
            break;
            case SDL_CONTROLLERBUTTONUP:
            {
                RED_LOG_TRACE("Gamepad button up");
            }
            break;
            case SDL_CONTROLLERDEVICEADDED:
            {
                RED_LOG_DEBUG("Gamepad ADDED");
            }
            break;
            case SDL_CONTROLLERDEVICEREMOVED:
            {
                RED_LOG_DEBUG("Gamepad REMOVED");
            }
            break;
        }
    }
}

}  // namespace red
