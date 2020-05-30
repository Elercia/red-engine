#include <RedEngine/Event/EventSystem.hpp>
#include <RedEngine/Input/InputDefinitionTranslationUnit.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <SDL2/SDL_events.h>

namespace red
{
EventSystem::EventSystem() : SubEngine(), m_quitRequested(false), m_keyStates(), m_mousePosition()
{
}

bool EventSystem::GetKey(red::KeyCodes::Enum key) const { return m_keyStates.at(key).isPressed; }

bool EventSystem::GetKeyUp(KeyCodes::Enum key) const { return m_keyStates.at(key).isUp; }

bool EventSystem::GetKeyDown(KeyCodes::Enum key) const { return m_keyStates.at(key).isDown; }

KeyState EventSystem::GetKeyState(KeyCodes::Enum key) const { return m_keyStates.at(key); }

const Vector2& EventSystem::GetMousePosition() const { return m_mousePosition; }

void EventSystem::SendKeyEvent(KeyCodes::Enum key, KeyEventType::Enum type)
{
    SDL_Event event;

    event.type = type == KeyEventType::KEY_DOWN ? SDL_KEYDOWN : SDL_KEYUP;
    event.key.keysym.scancode = g_keyboardSDLTranslationMap.at(key);

    SDL_PushEvent(&event);
}

void EventSystem::Update()
{
    // Reset the inputs
    // KeyDown and KeyUp only live for one frame
    for (auto& state : m_keyStates)
    {
        state.isDown = false;
        state.isUp = false;
    }

    // Update the inputs
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        /* handle your event here */
        switch (event.type)
        {
            // -------- WINDOW --------
            case SDL_WINDOWEVENT:
            {
                switch (event.window.event)
                {
                    case SDL_WINDOWEVENT_CLOSE:
                        m_quitRequested = true;
                        RED_LOG_DEBUG("Window event close");
                        break;
                    case SDL_WINDOWEVENT_MOVED:
                        RED_LOG_DEBUG("Window event mooved");
                        break;
                    case SDL_WINDOWEVENT_RESIZED:

                        CVar<int> windowHeight{"height", "window", 600};
                        CVar<int> windowWidth{"width", "window", 800};

                        windowHeight.ChangeValue(event.window.data2);
                        windowWidth.ChangeValue(event.window.data1);
                        m_windowResizeSignal(Vector2(event.window.data1, event.window.data2));
                        RED_LOG_DEBUG("Window event resized");
                        break;
                }
            }
            break;
                // -------- QUIT --------
            case SDL_QUIT:
                m_quitRequested = true;
                RED_LOG_DEBUG("Quit Requested");
                break;
                // -------- KEYS --------
            case SDL_KEYDOWN:
            {
                auto& keyState =
                    m_keyStates[g_keyboardTranslationMap.at(event.key.keysym.scancode)];

                if (!keyState.isPressed)
                {
                    keyState.isPressed = true;
                    keyState.isDown = true;

                    RED_LOG_DEBUG(
                        "Key DOWN {}",
                        g_keyCodeReadable[g_keyboardTranslationMap.at(event.key.keysym.scancode)]);
                }
            }
            break;
            case SDL_KEYUP:
            {
                auto& keyState =
                    m_keyStates[g_keyboardTranslationMap.at(event.key.keysym.scancode)];

                keyState.isPressed = false;
                keyState.isUp = true;

                RED_LOG_DEBUG(
                    "Key UP {}",
                    g_keyCodeReadable[g_keyboardTranslationMap.at(event.key.keysym.scancode)]);
            }
            break;
                // -------- MOUSE --------
            case SDL_MOUSEMOTION:
            {
                m_mousePosition = Vector2({event.motion.x, event.motion.y});
                RED_LOG_TRACE("Mouse motion {} {}", event.motion.x, event.motion.y);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                auto& keyState = m_keyStates[g_mouseTranslationUnit.at(event.button.button)];

                if (!keyState.isDown)
                {
                    keyState = {true, false, true};
                    RED_LOG_DEBUG(
                        "Mouse button DOWN {}",
                        g_keyCodeReadable[g_mouseTranslationUnit.at(event.button.button)]);
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                auto& keyState = m_keyStates[g_mouseTranslationUnit.at(event.button.button)];

                if (!keyState.isUp)
                {
                    keyState = {false, true, false};
                    RED_LOG_DEBUG(
                        "Mouse button UP {}",
                        g_keyCodeReadable[g_mouseTranslationUnit.at(event.button.button)]);
                }
            }
            break;
            case SDL_MOUSEWHEEL:
            {
                RED_LOG_DEBUG("Mouse wheel detected delta x:{}, y:{}", event.wheel.x,
                              event.wheel.y);
            }
            break;
                // -------- GAMEPAD --------
            case SDL_CONTROLLERAXISMOTION:
            {
                RED_LOG_DEBUG("Gamepad axis motion");
            }
            break;
            case SDL_CONTROLLERBUTTONDOWN:
            {
                RED_LOG_DEBUG("Gamepad button down");
            }
            break;
            case SDL_CONTROLLERBUTTONUP:
            {
                RED_LOG_DEBUG("Gamepad button up");
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

bool EventSystem::QuitRequested() const { return m_quitRequested; }

}  // namespace red
