#pragma once

#include <RedEngine/Input/InputDefinition.hpp>

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_gamecontroller.h>

#include <map>

namespace red
{
using SDLKeyboardTranslationMap = std::map<SDL_Scancode, KeyCodes::Enum>;
using KeyboardSDLTranslationMap = std::map<KeyCodes::Enum, SDL_Scancode>;

SDLKeyboardTranslationMap LoadSDLKeyboardTranslationMap()
{
    SDLKeyboardTranslationMap translationMap;

    translationMap[SDL_SCANCODE_A] = KeyCodes::KEY_A;
    translationMap[SDL_SCANCODE_B] = KeyCodes::KEY_B;
    translationMap[SDL_SCANCODE_C] = KeyCodes::KEY_C;
    translationMap[SDL_SCANCODE_D] = KeyCodes::KEY_D;
    translationMap[SDL_SCANCODE_E] = KeyCodes::KEY_E;
    translationMap[SDL_SCANCODE_F] = KeyCodes::KEY_F;
    translationMap[SDL_SCANCODE_G] = KeyCodes::KEY_G;
    translationMap[SDL_SCANCODE_H] = KeyCodes::KEY_H;
    translationMap[SDL_SCANCODE_I] = KeyCodes::KEY_I;
    translationMap[SDL_SCANCODE_J] = KeyCodes::KEY_J;
    translationMap[SDL_SCANCODE_K] = KeyCodes::KEY_K;
    translationMap[SDL_SCANCODE_L] = KeyCodes::KEY_L;
    translationMap[SDL_SCANCODE_M] = KeyCodes::KEY_M;
    translationMap[SDL_SCANCODE_N] = KeyCodes::KEY_N;
    translationMap[SDL_SCANCODE_O] = KeyCodes::KEY_O;
    translationMap[SDL_SCANCODE_P] = KeyCodes::KEY_P;
    translationMap[SDL_SCANCODE_Q] = KeyCodes::KEY_Q;
    translationMap[SDL_SCANCODE_R] = KeyCodes::KEY_R;
    translationMap[SDL_SCANCODE_S] = KeyCodes::KEY_S;
    translationMap[SDL_SCANCODE_T] = KeyCodes::KEY_T;
    translationMap[SDL_SCANCODE_U] = KeyCodes::KEY_U;
    translationMap[SDL_SCANCODE_V] = KeyCodes::KEY_V;
    translationMap[SDL_SCANCODE_W] = KeyCodes::KEY_W;
    translationMap[SDL_SCANCODE_X] = KeyCodes::KEY_X;
    translationMap[SDL_SCANCODE_Y] = KeyCodes::KEY_Y;
    translationMap[SDL_SCANCODE_Z] = KeyCodes::KEY_Z;
    translationMap[SDL_SCANCODE_1] = KeyCodes::KEY_1;
    translationMap[SDL_SCANCODE_2] = KeyCodes::KEY_2;
    translationMap[SDL_SCANCODE_3] = KeyCodes::KEY_3;
    translationMap[SDL_SCANCODE_4] = KeyCodes::KEY_4;
    translationMap[SDL_SCANCODE_5] = KeyCodes::KEY_5;
    translationMap[SDL_SCANCODE_6] = KeyCodes::KEY_6;
    translationMap[SDL_SCANCODE_7] = KeyCodes::KEY_7;
    translationMap[SDL_SCANCODE_8] = KeyCodes::KEY_8;
    translationMap[SDL_SCANCODE_9] = KeyCodes::KEY_9;
    translationMap[SDL_SCANCODE_0] = KeyCodes::KEY_0;
    translationMap[SDL_SCANCODE_RETURN] = KeyCodes::KEY_RETURN;
    translationMap[SDL_SCANCODE_ESCAPE] = KeyCodes::KEY_ESCAPE;
    translationMap[SDL_SCANCODE_BACKSPACE] = KeyCodes::KEY_BACKSPACE;
    translationMap[SDL_SCANCODE_TAB] = KeyCodes::KEY_TAB;
    translationMap[SDL_SCANCODE_SPACE] = KeyCodes::KEY_SPACE;
    translationMap[SDL_SCANCODE_MINUS] = KeyCodes::KEY_MINUS;
    translationMap[SDL_SCANCODE_EQUALS] = KeyCodes::KEY_EQUALS;
    translationMap[SDL_SCANCODE_LEFTBRACKET] = KeyCodes::KEY_LEFTBRACKET;
    translationMap[SDL_SCANCODE_RIGHTBRACKET] = KeyCodes::KEY_RIGHTBRACKET;
    translationMap[SDL_SCANCODE_BACKSLASH] = KeyCodes::KEY_BACKSLASH;
    translationMap[SDL_SCANCODE_NONUSHASH] = KeyCodes::KEY_NONUSHASH;
    translationMap[SDL_SCANCODE_SEMICOLON] = KeyCodes::KEY_SEMICOLON;
    translationMap[SDL_SCANCODE_APOSTROPHE] = KeyCodes::KEY_APOSTROPHE;
    translationMap[SDL_SCANCODE_GRAVE] = KeyCodes::KEY_GRAVE;
    translationMap[SDL_SCANCODE_COMMA] = KeyCodes::KEY_COMMA;
    translationMap[SDL_SCANCODE_PERIOD] = KeyCodes::KEY_PERIOD;
    translationMap[SDL_SCANCODE_SLASH] = KeyCodes::KEY_SLASH;
    translationMap[SDL_SCANCODE_CAPSLOCK] = KeyCodes::KEY_CAPSLOCK;
    translationMap[SDL_SCANCODE_F1] = KeyCodes::KEY_F1;
    translationMap[SDL_SCANCODE_F2] = KeyCodes::KEY_F2;
    translationMap[SDL_SCANCODE_F3] = KeyCodes::KEY_F3;
    translationMap[SDL_SCANCODE_F4] = KeyCodes::KEY_F4;
    translationMap[SDL_SCANCODE_F5] = KeyCodes::KEY_F5;
    translationMap[SDL_SCANCODE_F6] = KeyCodes::KEY_F6;
    translationMap[SDL_SCANCODE_F7] = KeyCodes::KEY_F7;
    translationMap[SDL_SCANCODE_F8] = KeyCodes::KEY_F8;
    translationMap[SDL_SCANCODE_F9] = KeyCodes::KEY_F9;
    translationMap[SDL_SCANCODE_F10] = KeyCodes::KEY_F10;
    translationMap[SDL_SCANCODE_F11] = KeyCodes::KEY_F11;
    translationMap[SDL_SCANCODE_F12] = KeyCodes::KEY_F12;
    translationMap[SDL_SCANCODE_PRINTSCREEN] = KeyCodes::KEY_PRINTSCREEN;
    translationMap[SDL_SCANCODE_SCROLLLOCK] = KeyCodes::KEY_SCROLLLOCK;
    translationMap[SDL_SCANCODE_PAUSE] = KeyCodes::KEY_PAUSE;
    translationMap[SDL_SCANCODE_INSERT] = KeyCodes::KEY_INSERT;
    translationMap[SDL_SCANCODE_HOME] = KeyCodes::KEY_HOME;
    translationMap[SDL_SCANCODE_PAGEUP] = KeyCodes::KEY_PAGEUP;
    translationMap[SDL_SCANCODE_DELETE] = KeyCodes::KEY_DELETE;
    translationMap[SDL_SCANCODE_END] = KeyCodes::KEY_END;
    translationMap[SDL_SCANCODE_PAGEDOWN] = KeyCodes::KEY_PAGEDOWN;
    translationMap[SDL_SCANCODE_RIGHT] = KeyCodes::KEY_RIGHT;
    translationMap[SDL_SCANCODE_LEFT] = KeyCodes::KEY_LEFT;
    translationMap[SDL_SCANCODE_DOWN] = KeyCodes::KEY_DOWN;
    translationMap[SDL_SCANCODE_UP] = KeyCodes::KEY_UP;
    translationMap[SDL_SCANCODE_NUMLOCKCLEAR] = KeyCodes::KEY_NUMLOCKCLEAR;
    translationMap[SDL_SCANCODE_KP_DIVIDE] = KeyCodes::KEY_KP_DIVIDE;
    translationMap[SDL_SCANCODE_KP_MULTIPLY] = KeyCodes::KEY_KP_MULTIPLY;
    translationMap[SDL_SCANCODE_KP_MINUS] = KeyCodes::KEY_KP_MINUS;
    translationMap[SDL_SCANCODE_KP_PLUS] = KeyCodes::KEY_KP_PLUS;
    translationMap[SDL_SCANCODE_KP_ENTER] = KeyCodes::KEY_KP_ENTER;
    translationMap[SDL_SCANCODE_KP_1] = KeyCodes::KEY_KP_1;
    translationMap[SDL_SCANCODE_KP_2] = KeyCodes::KEY_KP_2;
    translationMap[SDL_SCANCODE_KP_3] = KeyCodes::KEY_KP_3;
    translationMap[SDL_SCANCODE_KP_4] = KeyCodes::KEY_KP_4;
    translationMap[SDL_SCANCODE_KP_5] = KeyCodes::KEY_KP_5;
    translationMap[SDL_SCANCODE_KP_6] = KeyCodes::KEY_KP_6;
    translationMap[SDL_SCANCODE_KP_7] = KeyCodes::KEY_KP_7;
    translationMap[SDL_SCANCODE_KP_8] = KeyCodes::KEY_KP_8;
    translationMap[SDL_SCANCODE_KP_9] = KeyCodes::KEY_KP_9;
    translationMap[SDL_SCANCODE_KP_0] = KeyCodes::KEY_KP_0;
    translationMap[SDL_SCANCODE_KP_PERIOD] = KeyCodes::KEY_KP_PERIOD;
    translationMap[SDL_SCANCODE_NONUSBACKSLASH] = KeyCodes::KEY_NONUSBACKSLASH;
    translationMap[SDL_SCANCODE_APPLICATION] = KeyCodes::KEY_APPLICATION;
    translationMap[SDL_SCANCODE_POWER] = KeyCodes::KEY_POWER;
    translationMap[SDL_SCANCODE_KP_EQUALS] = KeyCodes::KEY_KP_EQUALS;
    translationMap[SDL_SCANCODE_F13] = KeyCodes::KEY_F13;
    translationMap[SDL_SCANCODE_F14] = KeyCodes::KEY_F14;
    translationMap[SDL_SCANCODE_F15] = KeyCodes::KEY_F15;
    translationMap[SDL_SCANCODE_F16] = KeyCodes::KEY_F16;
    translationMap[SDL_SCANCODE_F17] = KeyCodes::KEY_F17;
    translationMap[SDL_SCANCODE_F18] = KeyCodes::KEY_F18;
    translationMap[SDL_SCANCODE_F19] = KeyCodes::KEY_F19;
    translationMap[SDL_SCANCODE_F20] = KeyCodes::KEY_F20;
    translationMap[SDL_SCANCODE_F21] = KeyCodes::KEY_F21;
    translationMap[SDL_SCANCODE_F22] = KeyCodes::KEY_F22;
    translationMap[SDL_SCANCODE_F23] = KeyCodes::KEY_F23;
    translationMap[SDL_SCANCODE_F24] = KeyCodes::KEY_F24;
    translationMap[SDL_SCANCODE_EXECUTE] = KeyCodes::KEY_EXECUTE;
    translationMap[SDL_SCANCODE_HELP] = KeyCodes::KEY_HELP;
    translationMap[SDL_SCANCODE_MENU] = KeyCodes::KEY_MENU;
    translationMap[SDL_SCANCODE_SELECT] = KeyCodes::KEY_SELECT;
    translationMap[SDL_SCANCODE_STOP] = KeyCodes::KEY_STOP;
    translationMap[SDL_SCANCODE_AGAIN] = KeyCodes::KEY_AGAIN;
    translationMap[SDL_SCANCODE_UNDO] = KeyCodes::KEY_UNDO;
    translationMap[SDL_SCANCODE_CUT] = KeyCodes::KEY_CUT;
    translationMap[SDL_SCANCODE_COPY] = KeyCodes::KEY_COPY;
    translationMap[SDL_SCANCODE_PASTE] = KeyCodes::KEY_PASTE;
    translationMap[SDL_SCANCODE_FIND] = KeyCodes::KEY_FIND;
    translationMap[SDL_SCANCODE_MUTE] = KeyCodes::KEY_MUTE;
    translationMap[SDL_SCANCODE_VOLUMEUP] = KeyCodes::KEY_VOLUMEUP;
    translationMap[SDL_SCANCODE_VOLUMEDOWN] = KeyCodes::KEY_VOLUMEDOWN;
    translationMap[SDL_SCANCODE_KP_COMMA] = KeyCodes::KEY_KP_COMMA;
    translationMap[SDL_SCANCODE_KP_EQUALSAS400] = KeyCodes::KEY_KP_EQUALSAS400;
    translationMap[SDL_SCANCODE_INTERNATIONAL1] = KeyCodes::KEY_INTERNATIONAL1;
    translationMap[SDL_SCANCODE_INTERNATIONAL2] = KeyCodes::KEY_INTERNATIONAL2;
    translationMap[SDL_SCANCODE_INTERNATIONAL3] = KeyCodes::KEY_INTERNATIONAL3;
    translationMap[SDL_SCANCODE_INTERNATIONAL4] = KeyCodes::KEY_INTERNATIONAL4;
    translationMap[SDL_SCANCODE_INTERNATIONAL5] = KeyCodes::KEY_INTERNATIONAL5;
    translationMap[SDL_SCANCODE_INTERNATIONAL6] = KeyCodes::KEY_INTERNATIONAL6;
    translationMap[SDL_SCANCODE_INTERNATIONAL7] = KeyCodes::KEY_INTERNATIONAL7;
    translationMap[SDL_SCANCODE_INTERNATIONAL8] = KeyCodes::KEY_INTERNATIONAL8;
    translationMap[SDL_SCANCODE_INTERNATIONAL9] = KeyCodes::KEY_INTERNATIONAL9;
    translationMap[SDL_SCANCODE_LANG1] = KeyCodes::KEY_LANG1;
    translationMap[SDL_SCANCODE_LANG2] = KeyCodes::KEY_LANG2;
    translationMap[SDL_SCANCODE_LANG3] = KeyCodes::KEY_LANG3;
    translationMap[SDL_SCANCODE_LANG4] = KeyCodes::KEY_LANG4;
    translationMap[SDL_SCANCODE_LANG5] = KeyCodes::KEY_LANG5;
    translationMap[SDL_SCANCODE_LANG6] = KeyCodes::KEY_LANG6;
    translationMap[SDL_SCANCODE_LANG7] = KeyCodes::KEY_LANG7;
    translationMap[SDL_SCANCODE_LANG8] = KeyCodes::KEY_LANG8;
    translationMap[SDL_SCANCODE_LANG9] = KeyCodes::KEY_LANG9;
    translationMap[SDL_SCANCODE_ALTERASE] = KeyCodes::KEY_ALTERASE;
    translationMap[SDL_SCANCODE_SYSREQ] = KeyCodes::KEY_SYSREQ;
    translationMap[SDL_SCANCODE_CANCEL] = KeyCodes::KEY_CANCEL;
    translationMap[SDL_SCANCODE_CLEAR] = KeyCodes::KEY_CLEAR;
    translationMap[SDL_SCANCODE_PRIOR] = KeyCodes::KEY_PRIOR;
    translationMap[SDL_SCANCODE_RETURN2] = KeyCodes::KEY_RETURN2;
    translationMap[SDL_SCANCODE_SEPARATOR] = KeyCodes::KEY_SEPARATOR;
    translationMap[SDL_SCANCODE_OUT] = KeyCodes::KEY_OUT;
    translationMap[SDL_SCANCODE_OPER] = KeyCodes::KEY_OPER;
    translationMap[SDL_SCANCODE_CLEARAGAIN] = KeyCodes::KEY_CLEARAGAIN;
    translationMap[SDL_SCANCODE_CRSEL] = KeyCodes::KEY_CRSEL;
    translationMap[SDL_SCANCODE_EXSEL] = KeyCodes::KEY_EXSEL;
    translationMap[SDL_SCANCODE_KP_00] = KeyCodes::KEY_KP_00;
    translationMap[SDL_SCANCODE_KP_000] = KeyCodes::KEY_KP_000;
    translationMap[SDL_SCANCODE_THOUSANDSSEPARATOR] = KeyCodes::KEY_THOUSANDSSEPARATOR;
    translationMap[SDL_SCANCODE_DECIMALSEPARATOR] = KeyCodes::KEY_DECIMALSEPARATOR;
    translationMap[SDL_SCANCODE_CURRENCYUNIT] = KeyCodes::KEY_CURRENCYUNIT;
    translationMap[SDL_SCANCODE_CURRENCYSUBUNIT] = KeyCodes::KEY_CURRENCYSUBUNIT;
    translationMap[SDL_SCANCODE_KP_LEFTPAREN] = KeyCodes::KEY_KP_LEFTPAREN;
    translationMap[SDL_SCANCODE_KP_RIGHTPAREN] = KeyCodes::KEY_KP_RIGHTPAREN;
    translationMap[SDL_SCANCODE_KP_LEFTBRACE] = KeyCodes::KEY_KP_LEFTBRACE;
    translationMap[SDL_SCANCODE_KP_RIGHTBRACE] = KeyCodes::KEY_KP_RIGHTBRACE;
    translationMap[SDL_SCANCODE_KP_TAB] = KeyCodes::KEY_KP_TAB;
    translationMap[SDL_SCANCODE_KP_BACKSPACE] = KeyCodes::KEY_KP_BACKSPACE;
    translationMap[SDL_SCANCODE_KP_A] = KeyCodes::KEY_KP_A;
    translationMap[SDL_SCANCODE_KP_B] = KeyCodes::KEY_KP_B;
    translationMap[SDL_SCANCODE_KP_C] = KeyCodes::KEY_KP_C;
    translationMap[SDL_SCANCODE_KP_D] = KeyCodes::KEY_KP_D;
    translationMap[SDL_SCANCODE_KP_E] = KeyCodes::KEY_KP_E;
    translationMap[SDL_SCANCODE_KP_F] = KeyCodes::KEY_KP_F;
    translationMap[SDL_SCANCODE_KP_XOR] = KeyCodes::KEY_KP_XOR;
    translationMap[SDL_SCANCODE_KP_POWER] = KeyCodes::KEY_KP_POWER;
    translationMap[SDL_SCANCODE_KP_PERCENT] = KeyCodes::KEY_KP_PERCENT;
    translationMap[SDL_SCANCODE_KP_LESS] = KeyCodes::KEY_KP_LESS;
    translationMap[SDL_SCANCODE_KP_GREATER] = KeyCodes::KEY_KP_GREATER;
    translationMap[SDL_SCANCODE_KP_AMPERSAND] = KeyCodes::KEY_KP_AMPERSAND;
    translationMap[SDL_SCANCODE_KP_DBLAMPERSAND] = KeyCodes::KEY_KP_DBLAMPERSAND;
    translationMap[SDL_SCANCODE_KP_VERTICALBAR] = KeyCodes::KEY_KP_VERTICALBAR;
    translationMap[SDL_SCANCODE_KP_DBLVERTICALBAR] = KeyCodes::KEY_KP_DBLVERTICALBAR;
    translationMap[SDL_SCANCODE_KP_COLON] = KeyCodes::KEY_KP_COLON;
    translationMap[SDL_SCANCODE_KP_HASH] = KeyCodes::KEY_KP_HASH;
    translationMap[SDL_SCANCODE_KP_SPACE] = KeyCodes::KEY_KP_SPACE;
    translationMap[SDL_SCANCODE_KP_AT] = KeyCodes::KEY_KP_AT;
    translationMap[SDL_SCANCODE_KP_EXCLAM] = KeyCodes::KEY_KP_EXCLAM;
    translationMap[SDL_SCANCODE_KP_MEMSTORE] = KeyCodes::KEY_KP_MEMSTORE;
    translationMap[SDL_SCANCODE_KP_MEMRECALL] = KeyCodes::KEY_KP_MEMRECALL;
    translationMap[SDL_SCANCODE_KP_MEMCLEAR] = KeyCodes::KEY_KP_MEMCLEAR;
    translationMap[SDL_SCANCODE_KP_MEMADD] = KeyCodes::KEY_KP_MEMADD;
    translationMap[SDL_SCANCODE_KP_MEMSUBTRACT] = KeyCodes::KEY_KP_MEMSUBTRACT;
    translationMap[SDL_SCANCODE_KP_MEMMULTIPLY] = KeyCodes::KEY_KP_MEMMULTIPLY;
    translationMap[SDL_SCANCODE_KP_MEMDIVIDE] = KeyCodes::KEY_KP_MEMDIVIDE;
    translationMap[SDL_SCANCODE_KP_PLUSMINUS] = KeyCodes::KEY_KP_PLUSMINUS;
    translationMap[SDL_SCANCODE_KP_CLEAR] = KeyCodes::KEY_KP_CLEAR;
    translationMap[SDL_SCANCODE_KP_CLEARENTRY] = KeyCodes::KEY_KP_CLEARENTRY;
    translationMap[SDL_SCANCODE_KP_BINARY] = KeyCodes::KEY_KP_BINARY;
    translationMap[SDL_SCANCODE_KP_OCTAL] = KeyCodes::KEY_KP_OCTAL;
    translationMap[SDL_SCANCODE_KP_DECIMAL] = KeyCodes::KEY_KP_DECIMAL;
    translationMap[SDL_SCANCODE_KP_HEXADECIMAL] = KeyCodes::KEY_KP_HEXADECIMAL;
    translationMap[SDL_SCANCODE_LCTRL] = KeyCodes::KEY_LCTRL;
    translationMap[SDL_SCANCODE_LSHIFT] = KeyCodes::KEY_LSHIFT;
    translationMap[SDL_SCANCODE_LALT] = KeyCodes::KEY_LALT;
    translationMap[SDL_SCANCODE_LGUI] = KeyCodes::KEY_LGUI;
    translationMap[SDL_SCANCODE_RCTRL] = KeyCodes::KEY_RCTRL;
    translationMap[SDL_SCANCODE_RSHIFT] = KeyCodes::KEY_RSHIFT;
    translationMap[SDL_SCANCODE_RALT] = KeyCodes::KEY_RALT;
    translationMap[SDL_SCANCODE_RGUI] = KeyCodes::KEY_RGUI;
    translationMap[SDL_SCANCODE_MODE] = KeyCodes::KEY_MODE;
    translationMap[SDL_SCANCODE_AUDIONEXT] = KeyCodes::KEY_AUDIONEXT;
    translationMap[SDL_SCANCODE_AUDIOPREV] = KeyCodes::KEY_AUDIOPREV;
    translationMap[SDL_SCANCODE_AUDIOSTOP] = KeyCodes::KEY_AUDIOSTOP;
    translationMap[SDL_SCANCODE_AUDIOPLAY] = KeyCodes::KEY_AUDIOPLAY;
    translationMap[SDL_SCANCODE_AUDIOMUTE] = KeyCodes::KEY_AUDIOMUTE;
    translationMap[SDL_SCANCODE_MEDIASELECT] = KeyCodes::KEY_MEDIASELECT;
    translationMap[SDL_SCANCODE_WWW] = KeyCodes::KEY_WWW;
    translationMap[SDL_SCANCODE_MAIL] = KeyCodes::KEY_MAIL;
    translationMap[SDL_SCANCODE_CALCULATOR] = KeyCodes::KEY_CALCULATOR;
    translationMap[SDL_SCANCODE_COMPUTER] = KeyCodes::KEY_COMPUTER;
    translationMap[SDL_SCANCODE_AC_SEARCH] = KeyCodes::KEY_AC_SEARCH;
    translationMap[SDL_SCANCODE_AC_HOME] = KeyCodes::KEY_AC_HOME;
    translationMap[SDL_SCANCODE_AC_BACK] = KeyCodes::KEY_AC_BACK;
    translationMap[SDL_SCANCODE_AC_FORWARD] = KeyCodes::KEY_AC_FORWARD;
    translationMap[SDL_SCANCODE_AC_STOP] = KeyCodes::KEY_AC_STOP;
    translationMap[SDL_SCANCODE_AC_REFRESH] = KeyCodes::KEY_AC_REFRESH;
    translationMap[SDL_SCANCODE_AC_BOOKMARKS] = KeyCodes::KEY_AC_BOOKMARKS;
    translationMap[SDL_SCANCODE_BRIGHTNESSDOWN] = KeyCodes::KEY_BRIGHTNESSDOWN;
    translationMap[SDL_SCANCODE_BRIGHTNESSUP] = KeyCodes::KEY_BRIGHTNESSUP;
    translationMap[SDL_SCANCODE_DISPLAYSWITCH] = KeyCodes::KEY_DISPLAYSWITCH;
    translationMap[SDL_SCANCODE_KBDILLUMTOGGLE] = KeyCodes::KEY_KBDILLUMTOGGLE;
    translationMap[SDL_SCANCODE_KBDILLUMDOWN] = KeyCodes::KEY_KBDILLUMDOWN;
    translationMap[SDL_SCANCODE_KBDILLUMUP] = KeyCodes::KEY_KBDILLUMUP;
    translationMap[SDL_SCANCODE_EJECT] = KeyCodes::KEY_EJECT;
    translationMap[SDL_SCANCODE_SLEEP] = KeyCodes::KEY_SLEEP;
    translationMap[SDL_SCANCODE_APP1] = KeyCodes::KEY_APP1;
    translationMap[SDL_SCANCODE_APP2] = KeyCodes::KEY_APP2;

    return translationMap;
}

const SDLKeyboardTranslationMap g_keyboardTranslationMap = LoadSDLKeyboardTranslationMap();

KeyboardSDLTranslationMap LoadKeyboardSDLTranslationMap()
{
    KeyboardSDLTranslationMap map;

    for (auto& e : g_keyboardTranslationMap)
    {
        map[e.second] = e.first;
    }
    return map;
}

const KeyboardSDLTranslationMap g_keyboardSDLTranslationMap = LoadKeyboardSDLTranslationMap();

using SDLMouseButtonTranslationMap = std::map<Uint8 /* SDL scan code */, KeyCodes::Enum>;
SDLMouseButtonTranslationMap LoadSDLMouseTranslationMap()
{
    SDLMouseButtonTranslationMap translationMap;

    translationMap[SDL_BUTTON_LEFT] = KeyCodes::MOUSE_LEFT;
    translationMap[SDL_BUTTON_MIDDLE] = KeyCodes::MOUSE_MIDDLE;
    translationMap[SDL_BUTTON_RIGHT] = KeyCodes::MOUSE_RIGHT;
    translationMap[SDL_BUTTON_X1] = KeyCodes::MOUSE_X1;
    translationMap[SDL_BUTTON_X2] = KeyCodes::MOUSE_X2;

    return translationMap;
}

const SDLMouseButtonTranslationMap g_mouseTranslationUnit = LoadSDLMouseTranslationMap();

using SDLGamepadButtonTranslationMap = std::map<int /* SDL scan code */, KeyCodes::Enum>;
const SDLGamepadButtonTranslationMap g_gamepadTranslationUnit;  // TODO add the same for gamepad
}  // namespace red
