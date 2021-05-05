#pragma once

#include "RedEngine/Input/InputDefinition.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <map>

namespace red
{
using SDLKeyboardTranslationMap = std::map<SDL_Scancode, KeyCodes::Enum>;
using KeyboardSDLTranslationMap = std::map<KeyCodes::Enum, SDL_Scancode>;

SDLKeyboardTranslationMap GetSDLKeyboardTranslationMap();

KeyboardSDLTranslationMap GetKeyboardSDLTranslationMap();

using SDLMouseButtonTranslationMap = std::map<Uint8 /* SDL scan code */, KeyCodes::Enum>;

SDLMouseButtonTranslationMap GetSDLMouseTranslationMap();

using SDLGamepadButtonTranslationMap = std::map<int /* SDL scan code */, KeyCodes::Enum>;
}  // namespace red
