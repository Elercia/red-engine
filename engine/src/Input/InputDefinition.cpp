#include "RedEngine/Input/InputModule.hpp"
#include "RedEngine/Input/InputDefinition.hpp"

#include "RedEngine/Input/InputDefinitionTranslationUnit.hpp"

namespace red
{
SDLKeyboardTranslationMap GetSDLKeyboardTranslationMap()
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
    translationMap[SDL_SCANCODE_EXECUTE] = KeyCodes::KEY_EXEC;
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

KeyboardSDLTranslationMap GetKeyboardSDLTranslationMap()
{
    KeyboardSDLTranslationMap map;
    auto translation = GetSDLKeyboardTranslationMap();

    for (auto& e : translation)
    {
        map[e.second] = e.first;
    }
    return map;
}

SDLMouseButtonTranslationMap GetSDLMouseTranslationMap()
{
    SDLMouseButtonTranslationMap translationMap;

    translationMap[SDL_BUTTON_LEFT] = KeyCodes::MOUSE_LEFT;
    translationMap[SDL_BUTTON_MIDDLE] = KeyCodes::MOUSE_MIDDLE;
    translationMap[SDL_BUTTON_RIGHT] = KeyCodes::MOUSE_RIGHT;
    translationMap[SDL_BUTTON_X1] = KeyCodes::MOUSE_X1;
    translationMap[SDL_BUTTON_X2] = KeyCodes::MOUSE_X2;

    return translationMap;
}

KeyCodeReadableDb GetKeyCodeReadableDb()
{
    KeyCodeReadableDb db{};

    for (int i = 0; i < KeyCodes::MAX; ++i)
    {
        db[i] = "UNKNOWN";
    }

    db[KeyCodes::KEY_UNKNOWN] = "KEY_UNKNOWN";
    db[KeyCodes::KEY_A] = "KEY_A";
    db[KeyCodes::KEY_B] = "KEY_B";
    db[KeyCodes::KEY_C] = "KEY_C";
    db[KeyCodes::KEY_D] = "KEY_D";
    db[KeyCodes::KEY_E] = "KEY_E";
    db[KeyCodes::KEY_F] = "KEY_F";
    db[KeyCodes::KEY_G] = "KEY_G";
    db[KeyCodes::KEY_H] = "KEY_H";
    db[KeyCodes::KEY_I] = "KEY_I";
    db[KeyCodes::KEY_J] = "KEY_J";
    db[KeyCodes::KEY_K] = "KEY_K";
    db[KeyCodes::KEY_L] = "KEY_L";
    db[KeyCodes::KEY_M] = "KEY_M";
    db[KeyCodes::KEY_N] = "KEY_N";
    db[KeyCodes::KEY_O] = "KEY_O";
    db[KeyCodes::KEY_P] = "KEY_P";
    db[KeyCodes::KEY_Q] = "KEY_Q";
    db[KeyCodes::KEY_R] = "KEY_R";
    db[KeyCodes::KEY_S] = "KEY_S";
    db[KeyCodes::KEY_T] = "KEY_T";
    db[KeyCodes::KEY_U] = "KEY_U";
    db[KeyCodes::KEY_V] = "KEY_V";
    db[KeyCodes::KEY_W] = "KEY_W";
    db[KeyCodes::KEY_X] = "KEY_X";
    db[KeyCodes::KEY_Y] = "KEY_Y";
    db[KeyCodes::KEY_Z] = "KEY_Z";
    db[KeyCodes::KEY_1] = "KEY_1";
    db[KeyCodes::KEY_2] = "KEY_2";
    db[KeyCodes::KEY_3] = "KEY_3";
    db[KeyCodes::KEY_4] = "KEY_4";
    db[KeyCodes::KEY_5] = "KEY_5";
    db[KeyCodes::KEY_6] = "KEY_6";
    db[KeyCodes::KEY_7] = "KEY_7";
    db[KeyCodes::KEY_8] = "KEY_8";
    db[KeyCodes::KEY_9] = "KEY_9";
    db[KeyCodes::KEY_0] = "KEY_0";
    db[KeyCodes::KEY_RETURN] = "KEY_RETURN";
    db[KeyCodes::KEY_ESCAPE] = "KEY_ESCAPE";
    db[KeyCodes::KEY_BACKSPACE] = "KEY_BACKSPACE";
    db[KeyCodes::KEY_TAB] = "KEY_TAB";
    db[KeyCodes::KEY_SPACE] = "KEY_SPACE";
    db[KeyCodes::KEY_MINUS] = "KEY_MINUS";
    db[KeyCodes::KEY_EQUALS] = "KEY_EQUALS";
    db[KeyCodes::KEY_LEFTBRACKET] = "KEY_LEFTBRACKET";
    db[KeyCodes::KEY_RIGHTBRACKET] = "KEY_RIGHTBRACKET";
    db[KeyCodes::KEY_BACKSLASH] = "KEY_BACKSLASH";
    db[KeyCodes::KEY_NONUSHASH] = "KEY_NONUSHASH";
    db[KeyCodes::KEY_SEMICOLON] = "KEY_SEMICOLON";
    db[KeyCodes::KEY_APOSTROPHE] = "KEY_APOSTROPHE";
    db[KeyCodes::KEY_GRAVE] = "KEY_GRAVE";
    db[KeyCodes::KEY_COMMA] = "KEY_COMMA";
    db[KeyCodes::KEY_PERIOD] = "KEY_PERIOD";
    db[KeyCodes::KEY_SLASH] = "KEY_SLASH";
    db[KeyCodes::KEY_CAPSLOCK] = "KEY_CAPSLOCK";
    db[KeyCodes::KEY_F1] = "KEY_F1";
    db[KeyCodes::KEY_F2] = "KEY_F2";
    db[KeyCodes::KEY_F3] = "KEY_F3";
    db[KeyCodes::KEY_F4] = "KEY_F4";
    db[KeyCodes::KEY_F5] = "KEY_F5";
    db[KeyCodes::KEY_F6] = "KEY_F6";
    db[KeyCodes::KEY_F7] = "KEY_F7";
    db[KeyCodes::KEY_F8] = "KEY_F8";
    db[KeyCodes::KEY_F9] = "KEY_F9";
    db[KeyCodes::KEY_F10] = "KEY_F10";
    db[KeyCodes::KEY_F11] = "KEY_F11";
    db[KeyCodes::KEY_F12] = "KEY_F12";
    db[KeyCodes::KEY_PRINTSCREEN] = "KEY_PRINTSCREEN";
    db[KeyCodes::KEY_SCROLLLOCK] = "KEY_SCROLLLOCK";
    db[KeyCodes::KEY_PAUSE] = "KEY_PAUSE";
    db[KeyCodes::KEY_INSERT] = "KEY_INSERT";
    db[KeyCodes::KEY_HOME] = "KEY_HOME";
    db[KeyCodes::KEY_PAGEUP] = "KEY_PAGEUP";
    db[KeyCodes::KEY_DELETE] = "KEY_DELETE";
    db[KeyCodes::KEY_END] = "KEY_END";
    db[KeyCodes::KEY_PAGEDOWN] = "KEY_PAGEDOWN";
    db[KeyCodes::KEY_RIGHT] = "KEY_RIGHT";
    db[KeyCodes::KEY_LEFT] = "KEY_LEFT";
    db[KeyCodes::KEY_DOWN] = "KEY_DOWN";
    db[KeyCodes::KEY_UP] = "KEY_UP";
    db[KeyCodes::KEY_NUMLOCKCLEAR] = "KEY_NUMLOCKCLEAR";
    db[KeyCodes::KEY_KP_DIVIDE] = "KEY_KP_DIVIDE";
    db[KeyCodes::KEY_KP_MULTIPLY] = "KEY_KP_MULTIPLY";
    db[KeyCodes::KEY_KP_MINUS] = "KEY_KP_MINUS";
    db[KeyCodes::KEY_KP_PLUS] = "KEY_KP_PLUS";
    db[KeyCodes::KEY_KP_ENTER] = "KEY_KP_ENTER";
    db[KeyCodes::KEY_KP_1] = "KEY_KP_1";
    db[KeyCodes::KEY_KP_2] = "KEY_KP_2";
    db[KeyCodes::KEY_KP_3] = "KEY_KP_3";
    db[KeyCodes::KEY_KP_4] = "KEY_KP_4";
    db[KeyCodes::KEY_KP_5] = "KEY_KP_5";
    db[KeyCodes::KEY_KP_6] = "KEY_KP_6";
    db[KeyCodes::KEY_KP_7] = "KEY_KP_7";
    db[KeyCodes::KEY_KP_8] = "KEY_KP_8";
    db[KeyCodes::KEY_KP_9] = "KEY_KP_9";
    db[KeyCodes::KEY_KP_0] = "KEY_KP_0";
    db[KeyCodes::KEY_KP_PERIOD] = "KEY_KP_PERIOD";
    db[KeyCodes::KEY_NONUSBACKSLASH] = "KEY_NONUSBACKSLASH";
    db[KeyCodes::KEY_APPLICATION] = "KEY_APPLICATION";
    db[KeyCodes::KEY_POWER] = "KEY_POWER";
    db[KeyCodes::KEY_KP_EQUALS] = "KEY_KP_EQUALS";
    db[KeyCodes::KEY_F13] = "KEY_F13";
    db[KeyCodes::KEY_F14] = "KEY_F14";
    db[KeyCodes::KEY_F15] = "KEY_F15";
    db[KeyCodes::KEY_F16] = "KEY_F16";
    db[KeyCodes::KEY_F17] = "KEY_F17";
    db[KeyCodes::KEY_F18] = "KEY_F18";
    db[KeyCodes::KEY_F19] = "KEY_F19";
    db[KeyCodes::KEY_F20] = "KEY_F20";
    db[KeyCodes::KEY_F21] = "KEY_F21";
    db[KeyCodes::KEY_F22] = "KEY_F22";
    db[KeyCodes::KEY_F23] = "KEY_F23";
    db[KeyCodes::KEY_F24] = "KEY_F24";
    db[KeyCodes::KEY_EXEC] = "KEY_EXECUTE";
    db[KeyCodes::KEY_HELP] = "KEY_HELP";
    db[KeyCodes::KEY_MENU] = "KEY_MENU";
    db[KeyCodes::KEY_SELECT] = "KEY_SELECT";
    db[KeyCodes::KEY_STOP] = "KEY_STOP";
    db[KeyCodes::KEY_AGAIN] = "KEY_AGAIN";
    db[KeyCodes::KEY_UNDO] = "KEY_UNDO";
    db[KeyCodes::KEY_CUT] = "KEY_CUT";
    db[KeyCodes::KEY_COPY] = "KEY_COPY";
    db[KeyCodes::KEY_PASTE] = "KEY_PASTE";
    db[KeyCodes::KEY_FIND] = "KEY_FIND";
    db[KeyCodes::KEY_MUTE] = "KEY_MUTE";
    db[KeyCodes::KEY_VOLUMEUP] = "KEY_VOLUMEUP";
    db[KeyCodes::KEY_VOLUMEDOWN] = "KEY_VOLUMEDOWN";
    db[KeyCodes::KEY_KP_COMMA] = "KEY_KP_COMMA";
    db[KeyCodes::KEY_KP_EQUALSAS400] = "KEY_KP_EQUALSAS400";
    db[KeyCodes::KEY_INTERNATIONAL1] = "KEY_INTERNATIONAL1";
    db[KeyCodes::KEY_INTERNATIONAL2] = "KEY_INTERNATIONAL2";
    db[KeyCodes::KEY_INTERNATIONAL3] = "KEY_INTERNATIONAL3";
    db[KeyCodes::KEY_INTERNATIONAL4] = "KEY_INTERNATIONAL4";
    db[KeyCodes::KEY_INTERNATIONAL5] = "KEY_INTERNATIONAL5";
    db[KeyCodes::KEY_INTERNATIONAL6] = "KEY_INTERNATIONAL6";
    db[KeyCodes::KEY_INTERNATIONAL7] = "KEY_INTERNATIONAL7";
    db[KeyCodes::KEY_INTERNATIONAL8] = "KEY_INTERNATIONAL8";
    db[KeyCodes::KEY_INTERNATIONAL9] = "KEY_INTERNATIONAL9";
    db[KeyCodes::KEY_LANG1] = "KEY_LANG1";
    db[KeyCodes::KEY_LANG2] = "KEY_LANG2";
    db[KeyCodes::KEY_LANG3] = "KEY_LANG3";
    db[KeyCodes::KEY_LANG4] = "KEY_LANG4";
    db[KeyCodes::KEY_LANG5] = "KEY_LANG5";
    db[KeyCodes::KEY_LANG6] = "KEY_LANG6";
    db[KeyCodes::KEY_LANG7] = "KEY_LANG7";
    db[KeyCodes::KEY_LANG8] = "KEY_LANG8";
    db[KeyCodes::KEY_LANG9] = "KEY_LANG9";
    db[KeyCodes::KEY_ALTERASE] = "KEY_ALTERASE";
    db[KeyCodes::KEY_SYSREQ] = "KEY_SYSREQ";
    db[KeyCodes::KEY_CANCEL] = "KEY_CANCEL";
    db[KeyCodes::KEY_CLEAR] = "KEY_CLEAR";
    db[KeyCodes::KEY_PRIOR] = "KEY_PRIOR";
    db[KeyCodes::KEY_RETURN2] = "KEY_RETURN2";
    db[KeyCodes::KEY_SEPARATOR] = "KEY_SEPARATOR";
    db[KeyCodes::KEY_OUT] = "KEY_OUT";
    db[KeyCodes::KEY_OPER] = "KEY_OPER";
    db[KeyCodes::KEY_CLEARAGAIN] = "KEY_CLEARAGAIN";
    db[KeyCodes::KEY_CRSEL] = "KEY_CRSEL";
    db[KeyCodes::KEY_EXSEL] = "KEY_EXSEL";
    db[KeyCodes::KEY_KP_00] = "KEY_KP_00";
    db[KeyCodes::KEY_KP_000] = "KEY_KP_000";
    db[KeyCodes::KEY_THOUSANDSSEPARATOR] = "KEY_THOUSANDSSEPARATOR";
    db[KeyCodes::KEY_DECIMALSEPARATOR] = "KEY_DECIMALSEPARATOR";
    db[KeyCodes::KEY_CURRENCYUNIT] = "KEY_CURRENCYUNIT";
    db[KeyCodes::KEY_CURRENCYSUBUNIT] = "KEY_CURRENCYSUBUNIT";
    db[KeyCodes::KEY_KP_LEFTPAREN] = "KEY_KP_LEFTPAREN";
    db[KeyCodes::KEY_KP_RIGHTPAREN] = "KEY_KP_RIGHTPAREN";
    db[KeyCodes::KEY_KP_LEFTBRACE] = "KEY_KP_LEFTBRACE";
    db[KeyCodes::KEY_KP_RIGHTBRACE] = "KEY_KP_RIGHTBRACE";
    db[KeyCodes::KEY_KP_TAB] = "KEY_KP_TAB";
    db[KeyCodes::KEY_KP_BACKSPACE] = "KEY_KP_BACKSPACE";
    db[KeyCodes::KEY_KP_A] = "KEY_KP_A";
    db[KeyCodes::KEY_KP_B] = "KEY_KP_B";
    db[KeyCodes::KEY_KP_C] = "KEY_KP_C";
    db[KeyCodes::KEY_KP_D] = "KEY_KP_D";
    db[KeyCodes::KEY_KP_E] = "KEY_KP_E";
    db[KeyCodes::KEY_KP_F] = "KEY_KP_F";
    db[KeyCodes::KEY_KP_XOR] = "KEY_KP_XOR";
    db[KeyCodes::KEY_KP_POWER] = "KEY_KP_POWER";
    db[KeyCodes::KEY_KP_PERCENT] = "KEY_KP_PERCENT";
    db[KeyCodes::KEY_KP_LESS] = "KEY_KP_LESS";
    db[KeyCodes::KEY_KP_GREATER] = "KEY_KP_GREATER";
    db[KeyCodes::KEY_KP_AMPERSAND] = "KEY_KP_AMPERSAND";
    db[KeyCodes::KEY_KP_DBLAMPERSAND] = "KEY_KP_DBLAMPERSAND";
    db[KeyCodes::KEY_KP_VERTICALBAR] = "KEY_KP_VERTICALBAR";
    db[KeyCodes::KEY_KP_DBLVERTICALBAR] = "KEY_KP_DBLVERTICALBAR";
    db[KeyCodes::KEY_KP_COLON] = "KEY_KP_COLON";
    db[KeyCodes::KEY_KP_HASH] = "KEY_KP_HASH";
    db[KeyCodes::KEY_KP_SPACE] = "KEY_KP_SPACE";
    db[KeyCodes::KEY_KP_AT] = "KEY_KP_AT";
    db[KeyCodes::KEY_KP_EXCLAM] = "KEY_KP_EXCLAM";
    db[KeyCodes::KEY_KP_MEMSTORE] = "KEY_KP_MEMSTORE";
    db[KeyCodes::KEY_KP_MEMRECALL] = "KEY_KP_MEMRECALL";
    db[KeyCodes::KEY_KP_MEMCLEAR] = "KEY_KP_MEMCLEAR";
    db[KeyCodes::KEY_KP_MEMADD] = "KEY_KP_MEMADD";
    db[KeyCodes::KEY_KP_MEMSUBTRACT] = "KEY_KP_MEMSUBTRACT";
    db[KeyCodes::KEY_KP_MEMMULTIPLY] = "KEY_KP_MEMMULTIPLY";
    db[KeyCodes::KEY_KP_MEMDIVIDE] = "KEY_KP_MEMDIVIDE";
    db[KeyCodes::KEY_KP_PLUSMINUS] = "KEY_KP_PLUSMINUS";
    db[KeyCodes::KEY_KP_CLEAR] = "KEY_KP_CLEAR";
    db[KeyCodes::KEY_KP_CLEARENTRY] = "KEY_KP_CLEARENTRY";
    db[KeyCodes::KEY_KP_BINARY] = "KEY_KP_BINARY";
    db[KeyCodes::KEY_KP_OCTAL] = "KEY_KP_OCTAL";
    db[KeyCodes::KEY_KP_DECIMAL] = "KEY_KP_DECIMAL";
    db[KeyCodes::KEY_KP_HEXADECIMAL] = "KEY_KP_HEXADECIMAL";
    db[KeyCodes::KEY_LCTRL] = "KEY_LCTRL";
    db[KeyCodes::KEY_LSHIFT] = "KEY_LSHIFT";
    db[KeyCodes::KEY_LALT] = "KEY_LALT";
    db[KeyCodes::KEY_LGUI] = "KEY_LGUI";
    db[KeyCodes::KEY_RCTRL] = "KEY_RCTRL";
    db[KeyCodes::KEY_RSHIFT] = "KEY_RSHIFT";
    db[KeyCodes::KEY_RALT] = "KEY_RALT";
    db[KeyCodes::KEY_RGUI] = "KEY_RGUI";
    db[KeyCodes::KEY_MODE] = "KEY_MODE";
    db[KeyCodes::KEY_AUDIONEXT] = "KEY_AUDIONEXT";
    db[KeyCodes::KEY_AUDIOPREV] = "KEY_AUDIOPREV";
    db[KeyCodes::KEY_AUDIOSTOP] = "KEY_AUDIOSTOP";
    db[KeyCodes::KEY_AUDIOPLAY] = "KEY_AUDIOPLAY";
    db[KeyCodes::KEY_AUDIOMUTE] = "KEY_AUDIOMUTE";
    db[KeyCodes::KEY_MEDIASELECT] = "KEY_MEDIASELECT";
    db[KeyCodes::KEY_WWW] = "KEY_WWW";
    db[KeyCodes::KEY_MAIL] = "KEY_MAIL";
    db[KeyCodes::KEY_CALCULATOR] = "KEY_CALCULATOR";
    db[KeyCodes::KEY_COMPUTER] = "KEY_COMPUTER";
    db[KeyCodes::KEY_AC_SEARCH] = "KEY_AC_SEARCH";
    db[KeyCodes::KEY_AC_HOME] = "KEY_AC_HOME";
    db[KeyCodes::KEY_AC_BACK] = "KEY_AC_BACK";
    db[KeyCodes::KEY_AC_FORWARD] = "KEY_AC_FORWARD";
    db[KeyCodes::KEY_AC_STOP] = "KEY_AC_STOP";
    db[KeyCodes::KEY_AC_REFRESH] = "KEY_AC_REFRESH";
    db[KeyCodes::KEY_AC_BOOKMARKS] = "KEY_AC_BOOKMARKS";
    db[KeyCodes::KEY_BRIGHTNESSDOWN] = "KEY_BRIGHTNESSDOWN";
    db[KeyCodes::KEY_BRIGHTNESSUP] = "KEY_BRIGHTNESSUP";
    db[KeyCodes::KEY_DISPLAYSWITCH] = "KEY_DISPLAYSWITCH";
    db[KeyCodes::KEY_KBDILLUMTOGGLE] = "KEY_KBDILLUMTOGGLE";
    db[KeyCodes::KEY_KBDILLUMDOWN] = "KEY_KBDILLUMDOWN";
    db[KeyCodes::KEY_KBDILLUMUP] = "KEY_KBDILLUMUP";
    db[KeyCodes::KEY_EJECT] = "KEY_EJECT";
    db[KeyCodes::KEY_SLEEP] = "KEY_SLEEP";
    db[KeyCodes::KEY_APP1] = "KEY_APP1";
    db[KeyCodes::KEY_APP2] = "KEY_APP2";

    // Mouse buttons
    db[KeyCodes::MOUSE_LEFT] = "MOUSE_LEFT";
    db[KeyCodes::MOUSE_MIDDLE] = "MOUSE_MIDDLE";
    db[KeyCodes::MOUSE_RIGHT] = "MOUSE_RIGHT";
    db[KeyCodes::MOUSE_X1] = "MOUSE_X1";
    db[KeyCodes::MOUSE_X2] = "MOUSE_X2";

    // GAMEPAD
    db[KeyCodes::GAMEPAD_A] = "GAMEPAD_A";
    db[KeyCodes::GAMEPAD_B] = "GAMEPAD_B";
    db[KeyCodes::GAMEPAD_X] = "GAMEPAD_X";
    db[KeyCodes::GAMEPAD_Y] = "GAMEPAD_Y";
    db[KeyCodes::GAMEPAD_BACK] = "GAMEPAD_BACK";
    db[KeyCodes::GAMEPAD_GUIDE] = "GAMEPAD_GUIDE";
    db[KeyCodes::GAMEPAD_START] = "GAMEPAD_START";
    db[KeyCodes::GAMEPAD_LEFTSTICK] = "GAMEPAD_LEFTSTICK";
    db[KeyCodes::GAMEPAD_RIGHTSTICK] = "GAMEPAD_RIGHTSTICK";
    db[KeyCodes::GAMEPAD_LEFTSHOULDER] = "GAMEPAD_LEFTSHOULDER";
    db[KeyCodes::GAMEPAD_RIGHTSHOULDER] = "GAMEPAD_RIGHTSHOULDER";
    db[KeyCodes::GAMEPAD_DPAD_UP] = "GAMEPAD_DPAD_UP";
    db[KeyCodes::GAMEPAD_DPAD_DOWN] = "GAMEPAD_DPAD_DOWN";
    db[KeyCodes::GAMEPAD_DPAD_LEFT] = "GAMEPAD_DPAD_LEFT";
    db[KeyCodes::GAMEPAD_DPAD_RIGHT] = "GAMEPAD_DPAD_RIGHT";

    return db;
}
}  // namespace red
