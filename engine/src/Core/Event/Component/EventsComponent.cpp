#include "RedEngine/Core/Event/Component/EventsComponent.hpp"

#include "RedEngine/Input/InputDefinitionTranslationUnit.hpp"

#include <SDL2/SDL_events.h>

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(EventsComponent)

EventsComponent::EventsComponent(Entity* entity) : Component(entity), m_quitRequested(false)
{
}

EventsComponent::~EventsComponent()
{
}

bool EventsComponent::GetKey(KeyCodes::Enum key) const
{
    return m_keyStates.at(key).isPressed;
}

bool EventsComponent::GetKeyUp(KeyCodes::Enum key) const
{
    return m_keyStates.at(key).isUp;
}

bool EventsComponent::GetKeyDown(KeyCodes::Enum key) const
{
    return m_keyStates.at(key).isDown;
}

KeyState EventsComponent::GetKeyState(KeyCodes::Enum key) const
{
    return m_keyStates.at(key);
}

const Vector2i& EventsComponent::GetMousePosition() const
{
    return m_mousePosition;
}

void EventsComponent::SendKeyEvent(KeyCodes::Enum key, KeyEventType::Enum type)
{
    SDL_Event event;

    event.type = type == KeyEventType::KEY_DOWN ? SDL_KEYDOWN : SDL_KEYUP;
    event.key.keysym.scancode = GetKeyboardSDLTranslationMap().at(key);

    if (SDL_PushEvent(&event) < 0)
        RED_LOG_ERROR("Cant push event because : {}", SDL_GetError());
}

bool EventsComponent::QuitRequested() const
{
    return m_quitRequested;
}

}  // namespace red
