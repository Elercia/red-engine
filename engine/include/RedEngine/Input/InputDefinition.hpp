#pragma once

#include "RedEngine/RedEngineBase.hpp"

#include <array>

namespace red
{
struct KeyState
{
public:
    bool isPressed{false};
    bool isUp{false};
    bool isDown{false};
};

struct KeyEventType
{
    enum Enum
    {
        KEY_DOWN,
        KEY_UP
    };
};

struct KeyCodes
{
    enum Enum
    {
        /// Keyboard
        KEY_UNKNOWN,
        KEY_A,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,
        KEY_RETURN,
        KEY_ESCAPE,
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_SPACE,
        KEY_MINUS,
        KEY_EQUALS,
        KEY_LEFTBRACKET,
        KEY_RIGHTBRACKET,
        KEY_BACKSLASH,
        KEY_NONUSHASH,
        KEY_SEMICOLON,
        KEY_APOSTROPHE,
        KEY_GRAVE,
        KEY_COMMA,
        KEY_PERIOD,
        KEY_SLASH,
        KEY_CAPSLOCK,
        KEY_F1,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        KEY_PRINTSCREEN,
        KEY_SCROLLLOCK,
        KEY_PAUSE,
        KEY_INSERT,
        KEY_HOME,
        KEY_PAGEUP,
        KEY_DELETE,
        KEY_END,
        KEY_PAGEDOWN,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_DOWN,
        KEY_UP,
        KEY_NUMLOCKCLEAR,
        KEY_KP_DIVIDE,
        KEY_KP_MULTIPLY,
        KEY_KP_MINUS,
        KEY_KP_PLUS,
        KEY_KP_ENTER,
        KEY_KP_1,
        KEY_KP_2,
        KEY_KP_3,
        KEY_KP_4,
        KEY_KP_5,
        KEY_KP_6,
        KEY_KP_7,
        KEY_KP_8,
        KEY_KP_9,
        KEY_KP_0,
        KEY_KP_PERIOD,
        KEY_NONUSBACKSLASH,
        KEY_APPLICATION,
        KEY_POWER,
        KEY_KP_EQUALS,
        KEY_F13,
        KEY_F14,
        KEY_F15,
        KEY_F16,
        KEY_F17,
        KEY_F18,
        KEY_F19,
        KEY_F20,
        KEY_F21,
        KEY_F22,
        KEY_F23,
        KEY_F24,
        KEY_EXEC,
        KEY_HELP,
        KEY_MENU,
        KEY_SELECT,
        KEY_STOP,
        KEY_AGAIN,
        KEY_UNDO,
        KEY_CUT,
        KEY_COPY,
        KEY_PASTE,
        KEY_FIND,
        KEY_MUTE,
        KEY_VOLUMEUP,
        KEY_VOLUMEDOWN,
        KEY_KP_COMMA,
        KEY_KP_EQUALSAS400,
        KEY_INTERNATIONAL1,
        KEY_INTERNATIONAL2,
        KEY_INTERNATIONAL3,
        KEY_INTERNATIONAL4,
        KEY_INTERNATIONAL5,
        KEY_INTERNATIONAL6,
        KEY_INTERNATIONAL7,
        KEY_INTERNATIONAL8,
        KEY_INTERNATIONAL9,
        KEY_LANG1,
        KEY_LANG2,
        KEY_LANG3,
        KEY_LANG4,
        KEY_LANG5,
        KEY_LANG6,
        KEY_LANG7,
        KEY_LANG8,
        KEY_LANG9,
        KEY_ALTERASE,
        KEY_SYSREQ,
        KEY_CANCEL,
        KEY_CLEAR,
        KEY_PRIOR,
        KEY_RETURN2,
        KEY_SEPARATOR,
        KEY_OUT,
        KEY_OPER,
        KEY_CLEARAGAIN,
        KEY_CRSEL,
        KEY_EXSEL,
        KEY_KP_00,
        KEY_KP_000,
        KEY_THOUSANDSSEPARATOR,
        KEY_DECIMALSEPARATOR,
        KEY_CURRENCYUNIT,
        KEY_CURRENCYSUBUNIT,
        KEY_KP_LEFTPAREN,
        KEY_KP_RIGHTPAREN,
        KEY_KP_LEFTBRACE,
        KEY_KP_RIGHTBRACE,
        KEY_KP_TAB,
        KEY_KP_BACKSPACE,
        KEY_KP_A,
        KEY_KP_B,
        KEY_KP_C,
        KEY_KP_D,
        KEY_KP_E,
        KEY_KP_F,
        KEY_KP_XOR,
        KEY_KP_POWER,
        KEY_KP_PERCENT,
        KEY_KP_LESS,
        KEY_KP_GREATER,
        KEY_KP_AMPERSAND,
        KEY_KP_DBLAMPERSAND,
        KEY_KP_VERTICALBAR,
        KEY_KP_DBLVERTICALBAR,
        KEY_KP_COLON,
        KEY_KP_HASH,
        KEY_KP_SPACE,
        KEY_KP_AT,
        KEY_KP_EXCLAM,
        KEY_KP_MEMSTORE,
        KEY_KP_MEMRECALL,
        KEY_KP_MEMCLEAR,
        KEY_KP_MEMADD,
        KEY_KP_MEMSUBTRACT,
        KEY_KP_MEMMULTIPLY,
        KEY_KP_MEMDIVIDE,
        KEY_KP_PLUSMINUS,
        KEY_KP_CLEAR,
        KEY_KP_CLEARENTRY,
        KEY_KP_BINARY,
        KEY_KP_OCTAL,
        KEY_KP_DECIMAL,
        KEY_KP_HEXADECIMAL,
        KEY_LCTRL,
        KEY_LSHIFT,
        KEY_LALT,
        KEY_LGUI,
        KEY_RCTRL,
        KEY_RSHIFT,
        KEY_RALT,
        KEY_RGUI,
        KEY_MODE,
        KEY_AUDIONEXT,
        KEY_AUDIOPREV,
        KEY_AUDIOSTOP,
        KEY_AUDIOPLAY,
        KEY_AUDIOMUTE,
        KEY_MEDIASELECT,
        KEY_WWW,
        KEY_MAIL,
        KEY_CALCULATOR,
        KEY_COMPUTER,
        KEY_AC_SEARCH,
        KEY_AC_HOME,
        KEY_AC_BACK,
        KEY_AC_FORWARD,
        KEY_AC_STOP,
        KEY_AC_REFRESH,
        KEY_AC_BOOKMARKS,
        KEY_BRIGHTNESSDOWN,
        KEY_BRIGHTNESSUP,
        KEY_DISPLAYSWITCH,
        KEY_KBDILLUMTOGGLE,
        KEY_KBDILLUMDOWN,
        KEY_KBDILLUMUP,
        KEY_EJECT,
        KEY_SLEEP,
        KEY_APP1,
        KEY_APP2,
        /// Mouse buttons
        MOUSE_LEFT,
        MOUSE_MIDDLE,
        MOUSE_RIGHT,
        MOUSE_X1,
        MOUSE_X2,
        /// Gamepad
        GAMEPAD_A,
        GAMEPAD_B,
        GAMEPAD_X,
        GAMEPAD_Y,
        GAMEPAD_BACK,
        GAMEPAD_GUIDE,
        GAMEPAD_START,
        GAMEPAD_LEFTSTICK,
        GAMEPAD_RIGHTSTICK,
        GAMEPAD_LEFTSHOULDER,
        GAMEPAD_RIGHTSHOULDER,
        GAMEPAD_DPAD_UP,
        GAMEPAD_DPAD_DOWN,
        GAMEPAD_DPAD_LEFT,
        GAMEPAD_DPAD_RIGHT,

        MAX,
    };
};

using KeyCodeReadableDb = std::array<const char*, KeyCodes::MAX>;

constexpr KeyCodeReadableDb InitKeyCodeReadableDb()
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
constexpr KeyCodeReadableDb g_keyCodeReadable = InitKeyCodeReadableDb();

}  // namespace red
