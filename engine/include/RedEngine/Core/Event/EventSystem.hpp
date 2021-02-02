#pragma once

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Event/Delegate.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Core/SubEngine.hpp"
#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/Math/Point.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <array>

namespace red
{
class EventSystem : public SubEngine
{
public:
    EventSystem();
    ~EventSystem() = default;

    [[nodiscard]] bool GetKey(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyUp(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyDown(KeyCodes::Enum key) const;

    [[nodiscard]] KeyState GetKeyState(KeyCodes::Enum key) const;

    [[nodiscard]] const Point& GetMousePosition() const;

    [[nodiscard]] bool QuitRequested() const;

    void Update();

    void SendKeyEvent(KeyCodes::Enum key, KeyEventType::Enum type);

private:
    bool m_quitRequested;
    Point m_mousePosition;

    std::array<KeyState, KeyCodes::MAX> m_keyStates;

    // TODO make more signals (mouse move, key pressed / released)
    Signal<Point> m_windowResizeSignal;
};
}  // namespace red
