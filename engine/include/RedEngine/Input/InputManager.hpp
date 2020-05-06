#pragma once

#include <array>
#include <RedEngine/Core/SubEngine.hpp>
#include <RedEngine/Input/InputDefinition.hpp>
#include <RedEngine/Math/Vector.hpp>
#include <RedEngine/Event/Delegate.hpp>

namespace red
{
struct KeyState
{
public:
    bool isPressed{false};
    bool isUp{false};
    bool isDown{false};
};

class InputManager : public SubEngine
{
public:
    InputManager();
    ~InputManager() = default;

    [[nodiscard]] bool GetKey(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyUp(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyDown(KeyCodes::Enum key) const;

    [[nodiscard]] bool GetMouseButton(MouseButtons::Enum button) const;
    [[nodiscard]] bool GetMouseButtonUp(MouseButtons::Enum button) const;
    [[nodiscard]] bool GetMouseButtonDown(MouseButtons::Enum button) const;

    [[nodiscard]] const Vector2& GetMousePosition() const;

    [[nodiscard]] bool QuitRequested() const;

    void Update();

private:
    bool m_quitRequested;
    Vector2 m_mousePosition;

    std::array<KeyState, KeyCodes::MAX_KEYS> m_keyStates;
    std::array<KeyState, MouseButtons::MAX_BUTTONS> m_mouseButtonState;

    Delegate<Vector2> m_windowResizeEvent;
};
}  // namespace red
