#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Event/Signal.hpp"
#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/Math/Vector.hpp"

namespace red
{
class EventsComponent : public Component
{
    friend class EventSystem;

public:
    RED_START_COMPONENT_REGISTER_INHERITHED(EventsComponent, Component)
    RED_END_COMPONENT_REGISTER()

    EventsComponent(Entity* entity);
    ~EventsComponent();

    [[nodiscard]] bool GetKey(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyUp(KeyCodes::Enum key) const;
    [[nodiscard]] bool GetKeyDown(KeyCodes::Enum key) const;

    [[nodiscard]] KeyState GetKeyState(KeyCodes::Enum key) const;

    [[nodiscard]] const Vector2i& GetMousePosition() const;

    [[nodiscard]] bool QuitRequested() const;

    void SendKeyEvent(KeyCodes::Enum key, KeyEventType::Enum type);

private:
    bool m_quitRequested;
    Vector2i m_mousePosition;

    std::array<KeyState, KeyCodes::MAX> m_keyStates;

    // TODO make more signals (mouse move, key pressed / released)
    Signal<Vector2i> m_windowResizeSignal;
};
}  // namespace red