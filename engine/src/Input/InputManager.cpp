#include <RedEngine/Input/InputManager.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>
#include <SDL2/SDL_events.h>

namespace red
{
InputManager::InputManager()
    : SubEngine(), m_quitRequested(false), m_keyStates(), m_mouseButtonState(), m_mousePosition()
{
}

bool InputManager::GetKey(red::KeyCodes::Enum key) const { return m_keyStates[key].isPressed; }

bool InputManager::GetKeyUp(KeyCodes::Enum key) const { return m_keyStates[key].isUp; }

bool InputManager::GetKeyDown(KeyCodes::Enum key) const { return m_keyStates[key].isDown; }

bool InputManager::GetMouseButton(MouseButtons::Enum button) const
{
    return m_mouseButtonState[button].isPressed;
}

bool InputManager::GetMouseButtonUp(MouseButtons::Enum button) const
{
    return m_mouseButtonState[button].isUp;
}

bool InputManager::GetMouseButtonDown(MouseButtons::Enum button) const
{
    return m_mouseButtonState[button].isDown;
}

const Vector2& InputManager::GetMousePosition() const { return m_mousePosition; }

void InputManager::Update()
{
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
                auto& keyState = m_keyStates[event.key.keysym.scancode];

                if (!keyState.isDown)
                {
                    keyState = {true, false, true};
                    RED_LOG_DEBUG("Key DOWN {}", g_keyCodeReadable[event.key.keysym.scancode]);
                }
            }
            break;
            case SDL_KEYUP:
            {
                auto& keyState = m_keyStates[event.key.keysym.scancode];

                if (!keyState.isUp)
                {
                    keyState = {false, true, false};
                    RED_LOG_DEBUG("Key UP {}", g_keyCodeReadable[event.key.keysym.scancode]);
                }
            }
            break;
                // -------- MOUSE --------
            case SDL_MOUSEMOTION:
            {
                m_mousePosition = Vector2({event.motion.x, event.motion.y});
                RED_LOG_DEBUG("Mouse motion {} {}", event.motion.x, event.motion.y);
            }
            break;
            case SDL_MOUSEBUTTONDOWN:
            {
                auto& keyState = m_mouseButtonState[event.button.button];

                if (!keyState.isDown)
                {
                    keyState = {true, false, true};
                    RED_LOG_DEBUG("Mouse button DOWN {}",
                                  g_mouseButtonsReadable[event.button.button]);
                }
            }
            break;
            case SDL_MOUSEBUTTONUP:
            {
                auto& keyState = m_mouseButtonState[event.button.button];

                if (!keyState.isUp)
                {
                    keyState = {false, true, false};
                    RED_LOG_DEBUG("Mouse button UP {}",
                                  g_mouseButtonsReadable[event.button.button]);
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

bool InputManager::QuitRequested() const { return m_quitRequested; }

}  // namespace red
