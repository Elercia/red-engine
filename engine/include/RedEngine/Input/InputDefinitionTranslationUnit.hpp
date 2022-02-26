#pragma once

#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Input/InputDefinition.hpp"

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>

namespace red
{
using SDLKeyboardTranslationMap = Map<SDL_Scancode, KeyCodes::Enum>;
using KeyboardSDLTranslationMap = Map<KeyCodes::Enum, SDL_Scancode>;

SDLKeyboardTranslationMap GetSDLKeyboardTranslationMap();

KeyboardSDLTranslationMap GetKeyboardSDLTranslationMap();

using SDLMouseButtonTranslationMap = Map<Uint8 /* SDL scan code */, KeyCodes::Enum>;

SDLMouseButtonTranslationMap GetSDLMouseTranslationMap();

using SDLGamepadButtonTranslationMap = Map<int /* SDL scan code */, KeyCodes::Enum>;
}  // namespace red
