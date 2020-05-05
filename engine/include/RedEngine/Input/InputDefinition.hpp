#pragma once

#include <array>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_gamecontroller.h>

namespace red
{
struct KeyCodes
{
    enum Enum
    {
        KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN,
        KEY_A = SDL_SCANCODE_A,
        KEY_B = SDL_SCANCODE_B,
        KEY_C = SDL_SCANCODE_C,
        KEY_D = SDL_SCANCODE_D,
        KEY_E = SDL_SCANCODE_E,
        KEY_F = SDL_SCANCODE_F,
        KEY_G = SDL_SCANCODE_G,
        KEY_H = SDL_SCANCODE_H,
        KEY_I = SDL_SCANCODE_I,
        KEY_J = SDL_SCANCODE_J,
        KEY_K = SDL_SCANCODE_K,
        KEY_L = SDL_SCANCODE_L,
        KEY_M = SDL_SCANCODE_M,
        KEY_N = SDL_SCANCODE_N,
        KEY_O = SDL_SCANCODE_O,
        KEY_P = SDL_SCANCODE_P,
        KEY_Q = SDL_SCANCODE_Q,
        KEY_R = SDL_SCANCODE_R,
        KEY_S = SDL_SCANCODE_S,
        KEY_T = SDL_SCANCODE_T,
        KEY_U = SDL_SCANCODE_U,
        KEY_V = SDL_SCANCODE_V,
        KEY_W = SDL_SCANCODE_W,
        KEY_X = SDL_SCANCODE_X,
        KEY_Y = SDL_SCANCODE_Y,
        KEY_Z = SDL_SCANCODE_Z,
        KEY_1 = SDL_SCANCODE_1,
        KEY_2 = SDL_SCANCODE_2,
        KEY_3 = SDL_SCANCODE_3,
        KEY_4 = SDL_SCANCODE_4,
        KEY_5 = SDL_SCANCODE_5,
        KEY_6 = SDL_SCANCODE_6,
        KEY_7 = SDL_SCANCODE_7,
        KEY_8 = SDL_SCANCODE_8,
        KEY_9 = SDL_SCANCODE_9,
        KEY_0 = SDL_SCANCODE_0,
        KEY_RETURN = SDL_SCANCODE_RETURN,
        KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
        KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        KEY_TAB = SDL_SCANCODE_TAB,
        KEY_SPACE = SDL_SCANCODE_SPACE,
        KEY_MINUS = SDL_SCANCODE_MINUS,
        KEY_EQUALS = SDL_SCANCODE_EQUALS,
        KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET,
        KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET,
        KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
        KEY_NONUSHASH = SDL_SCANCODE_NONUSHASH,
        KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
        KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
        KEY_GRAVE = SDL_SCANCODE_GRAVE,
        KEY_COMMA = SDL_SCANCODE_COMMA,
        KEY_PERIOD = SDL_SCANCODE_PERIOD,
        KEY_SLASH = SDL_SCANCODE_SLASH,
        KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,
        KEY_F1 = SDL_SCANCODE_F1,
        KEY_F2 = SDL_SCANCODE_F2,
        KEY_F3 = SDL_SCANCODE_F3,
        KEY_F4 = SDL_SCANCODE_F4,
        KEY_F5 = SDL_SCANCODE_F5,
        KEY_F6 = SDL_SCANCODE_F6,
        KEY_F7 = SDL_SCANCODE_F7,
        KEY_F8 = SDL_SCANCODE_F8,
        KEY_F9 = SDL_SCANCODE_F9,
        KEY_F10 = SDL_SCANCODE_F10,
        KEY_F11 = SDL_SCANCODE_F11,
        KEY_F12 = SDL_SCANCODE_F12,
        KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
        KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
        KEY_PAUSE = SDL_SCANCODE_PAUSE,
        KEY_INSERT = SDL_SCANCODE_INSERT,
        KEY_HOME = SDL_SCANCODE_HOME,
        KEY_PAGEUP = SDL_SCANCODE_PAGEUP,
        KEY_DELETE = SDL_SCANCODE_DELETE,
        KEY_END = SDL_SCANCODE_END,
        KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
        KEY_RIGHT = SDL_SCANCODE_RIGHT,
        KEY_LEFT = SDL_SCANCODE_LEFT,
        KEY_DOWN = SDL_SCANCODE_DOWN,
        KEY_UP = SDL_SCANCODE_UP,
        KEY_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR,
        KEY_KP_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
        KEY_KP_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
        KEY_KP_MINUS = SDL_SCANCODE_KP_MINUS,
        KEY_KP_PLUS = SDL_SCANCODE_KP_PLUS,
        KEY_KP_ENTER = SDL_SCANCODE_KP_ENTER,
        KEY_KP_1 = SDL_SCANCODE_KP_1,
        KEY_KP_2 = SDL_SCANCODE_KP_2,
        KEY_KP_3 = SDL_SCANCODE_KP_3,
        KEY_KP_4 = SDL_SCANCODE_KP_4,
        KEY_KP_5 = SDL_SCANCODE_KP_5,
        KEY_KP_6 = SDL_SCANCODE_KP_6,
        KEY_KP_7 = SDL_SCANCODE_KP_7,
        KEY_KP_8 = SDL_SCANCODE_KP_8,
        KEY_KP_9 = SDL_SCANCODE_KP_9,
        KEY_KP_0 = SDL_SCANCODE_KP_0,
        KEY_KP_PERIOD = SDL_SCANCODE_KP_PERIOD,
        KEY_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH,
        KEY_APPLICATION = SDL_SCANCODE_APPLICATION,
        KEY_POWER = SDL_SCANCODE_POWER,
        KEY_KP_EQUALS = SDL_SCANCODE_KP_EQUALS,
        KEY_F13 = SDL_SCANCODE_F13,
        KEY_F14 = SDL_SCANCODE_F14,
        KEY_F15 = SDL_SCANCODE_F15,
        KEY_F16 = SDL_SCANCODE_F16,
        KEY_F17 = SDL_SCANCODE_F17,
        KEY_F18 = SDL_SCANCODE_F18,
        KEY_F19 = SDL_SCANCODE_F19,
        KEY_F20 = SDL_SCANCODE_F20,
        KEY_F21 = SDL_SCANCODE_F21,
        KEY_F22 = SDL_SCANCODE_F22,
        KEY_F23 = SDL_SCANCODE_F23,
        KEY_F24 = SDL_SCANCODE_F24,
        KEY_EXECUTE = SDL_SCANCODE_EXECUTE,
        KEY_HELP = SDL_SCANCODE_HELP,
        KEY_MENU = SDL_SCANCODE_MENU,
        KEY_SELECT = SDL_SCANCODE_SELECT,
        KEY_STOP = SDL_SCANCODE_STOP,
        KEY_AGAIN = SDL_SCANCODE_AGAIN,
        KEY_UNDO = SDL_SCANCODE_UNDO,
        KEY_CUT = SDL_SCANCODE_CUT,
        KEY_COPY = SDL_SCANCODE_COPY,
        KEY_PASTE = SDL_SCANCODE_PASTE,
        KEY_FIND = SDL_SCANCODE_FIND,
        KEY_MUTE = SDL_SCANCODE_MUTE,
        KEY_VOLUMEUP = SDL_SCANCODE_VOLUMEUP,
        KEY_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN,
        KEY_KP_COMMA = SDL_SCANCODE_KP_COMMA,
        KEY_KP_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400,
        KEY_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1,
        KEY_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2,
        KEY_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3,
        KEY_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4,
        KEY_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5,
        KEY_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6,
        KEY_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7,
        KEY_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8,
        KEY_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9,
        KEY_LANG1 = SDL_SCANCODE_LANG1,
        KEY_LANG2 = SDL_SCANCODE_LANG2,
        KEY_LANG3 = SDL_SCANCODE_LANG3,
        KEY_LANG4 = SDL_SCANCODE_LANG4,
        KEY_LANG5 = SDL_SCANCODE_LANG5,
        KEY_LANG6 = SDL_SCANCODE_LANG6,
        KEY_LANG7 = SDL_SCANCODE_LANG7,
        KEY_LANG8 = SDL_SCANCODE_LANG8,
        KEY_LANG9 = SDL_SCANCODE_LANG9,
        KEY_ALTERASE = SDL_SCANCODE_ALTERASE,
        KEY_SYSREQ = SDL_SCANCODE_SYSREQ,
        KEY_CANCEL = SDL_SCANCODE_CANCEL,
        KEY_CLEAR = SDL_SCANCODE_CLEAR,
        KEY_PRIOR = SDL_SCANCODE_PRIOR,
        KEY_RETURN2 = SDL_SCANCODE_RETURN2,
        KEY_SEPARATOR = SDL_SCANCODE_SEPARATOR,
        KEY_OUT = SDL_SCANCODE_OUT,
        KEY_OPER = SDL_SCANCODE_OPER,
        KEY_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN,
        KEY_CRSEL = SDL_SCANCODE_CRSEL,
        KEY_EXSEL = SDL_SCANCODE_EXSEL,
        KEY_KP_00 = SDL_SCANCODE_KP_00,
        KEY_KP_000 = SDL_SCANCODE_KP_000,
        KEY_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR,
        KEY_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR,
        KEY_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT,
        KEY_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT,
        KEY_KP_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN,
        KEY_KP_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN,
        KEY_KP_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE,
        KEY_KP_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE,
        KEY_KP_TAB = SDL_SCANCODE_KP_TAB,
        KEY_KP_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE,
        KEY_KP_A = SDL_SCANCODE_KP_A,
        KEY_KP_B = SDL_SCANCODE_KP_B,
        KEY_KP_C = SDL_SCANCODE_KP_C,
        KEY_KP_D = SDL_SCANCODE_KP_D,
        KEY_KP_E = SDL_SCANCODE_KP_E,
        KEY_KP_F = SDL_SCANCODE_KP_F,
        KEY_KP_XOR = SDL_SCANCODE_KP_XOR,
        KEY_KP_POWER = SDL_SCANCODE_KP_POWER,
        KEY_KP_PERCENT = SDL_SCANCODE_KP_PERCENT,
        KEY_KP_LESS = SDL_SCANCODE_KP_LESS,
        KEY_KP_GREATER = SDL_SCANCODE_KP_GREATER,
        KEY_KP_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND,
        KEY_KP_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND,
        KEY_KP_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR,
        KEY_KP_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR,
        KEY_KP_COLON = SDL_SCANCODE_KP_COLON,
        KEY_KP_HASH = SDL_SCANCODE_KP_HASH,
        KEY_KP_SPACE = SDL_SCANCODE_KP_SPACE,
        KEY_KP_AT = SDL_SCANCODE_KP_AT,
        KEY_KP_EXCLAM = SDL_SCANCODE_KP_EXCLAM,
        KEY_KP_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE,
        KEY_KP_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL,
        KEY_KP_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR,
        KEY_KP_MEMADD = SDL_SCANCODE_KP_MEMADD,
        KEY_KP_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT,
        KEY_KP_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY,
        KEY_KP_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE,
        KEY_KP_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS,
        KEY_KP_CLEAR = SDL_SCANCODE_KP_CLEAR,
        KEY_KP_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY,
        KEY_KP_BINARY = SDL_SCANCODE_KP_BINARY,
        KEY_KP_OCTAL = SDL_SCANCODE_KP_OCTAL,
        KEY_KP_DECIMAL = SDL_SCANCODE_KP_DECIMAL,
        KEY_KP_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL,
        KEY_LCTRL = SDL_SCANCODE_LCTRL,
        KEY_LSHIFT = SDL_SCANCODE_LSHIFT,
        KEY_LALT = SDL_SCANCODE_LALT,
        KEY_LGUI = SDL_SCANCODE_LGUI,
        KEY_RCTRL = SDL_SCANCODE_RCTRL,
        KEY_RSHIFT = SDL_SCANCODE_RSHIFT,
        KEY_RALT = SDL_SCANCODE_RALT,
        KEY_RGUI = SDL_SCANCODE_RGUI,
        KEY_MODE = SDL_SCANCODE_MODE,
        KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT,
        KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV,
        KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP,
        KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY,
        KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE,
        KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT,
        KEY_WWW = SDL_SCANCODE_WWW,
        KEY_MAIL = SDL_SCANCODE_MAIL,
        KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR,
        KEY_COMPUTER = SDL_SCANCODE_COMPUTER,
        KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
        KEY_AC_HOME = SDL_SCANCODE_AC_HOME,
        KEY_AC_BACK = SDL_SCANCODE_AC_BACK,
        KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
        KEY_AC_STOP = SDL_SCANCODE_AC_STOP,
        KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
        KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,
        KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN,
        KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP,
        KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH,
        KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE,
        KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN,
        KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP,
        KEY_EJECT = SDL_SCANCODE_EJECT,
        KEY_SLEEP = SDL_SCANCODE_SLEEP,
        KEY_APP1 = SDL_SCANCODE_APP1,
        KEY_APP2 = SDL_SCANCODE_APP2,
        MAX_KEYS
    };
};

struct MouseButtons
{
    enum Enum
    {
        MOUSE_LEFT = SDL_BUTTON_LEFT,
        MOUSE_MIDDLE = SDL_BUTTON_MIDDLE,
        MOUSE_RIGHT = SDL_BUTTON_RIGHT,
        MOUSE_X1 = SDL_BUTTON_X1,
        MOUSE_X2 = SDL_BUTTON_X2,
        MAX_BUTTONS
    };
};

struct GamepadButtons
{
    enum Enum
    {
        A = SDL_CONTROLLER_BUTTON_A,
        B = SDL_CONTROLLER_BUTTON_B,
        X = SDL_CONTROLLER_BUTTON_X,
        Y = SDL_CONTROLLER_BUTTON_Y,
        BACK = SDL_CONTROLLER_BUTTON_BACK,
        GUIDE = SDL_CONTROLLER_BUTTON_GUIDE,
        START = SDL_CONTROLLER_BUTTON_START,
        LEFTSTICK = SDL_CONTROLLER_BUTTON_LEFTSTICK,
        RIGHTSTICK = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
        LEFTSHOULDER = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
        RIGHTSHOULDER = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
        DPAD_UP = SDL_CONTROLLER_BUTTON_DPAD_UP,
        DPAD_DOWN = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
        DPAD_LEFT = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
        DPAD_RIGHT = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
        MAX = SDL_CONTROLLER_BUTTON_MAX,
    };
};

struct GamepadJoystickAxis
{
    enum Enum
    {
        AXIS_LEFTX = SDL_CONTROLLER_AXIS_LEFTX,
        AXIS_LEFTY = SDL_CONTROLLER_AXIS_LEFTY,
        AXIS_RIGHTX = SDL_CONTROLLER_AXIS_RIGHTX,
        AXIS_RIGHTY = SDL_CONTROLLER_AXIS_RIGHTY,
        AXIS_TRIGGERLEFT = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
        AXIS_TRIGGERRIGHT = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
        AXIS_MAX = SDL_CONTROLLER_AXIS_MAX,
    };
};

using KeyCodeReadableDb = std::array<const char*, KeyCodes::MAX_KEYS>;
using MouseButtonsReadableDb = std::array<const char*, MouseButtons::MAX_BUTTONS>;
using GamepasButtonsReadableDb = std::array<const char*, GamepadButtons::MAX>;
using GamepasJoystickReadableDb = std::array<const char*, GamepadJoystickAxis::AXIS_MAX>;

constexpr KeyCodeReadableDb InitKeyCodeReadableDb()
{
    KeyCodeReadableDb db{};

    for (int i = 0; i < KeyCodes::MAX_KEYS; ++i)
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
    db[KeyCodes::KEY_EXECUTE] = "KEY_EXECUTE";
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

    return db;
}
constexpr KeyCodeReadableDb g_keyCodeReadable = InitKeyCodeReadableDb();

constexpr MouseButtonsReadableDb InitMouseButtonsReadableDb()
{
    MouseButtonsReadableDb db{};

    for (int i = 0; i < MouseButtons::MAX_BUTTONS; ++i)
    {
        db[i] = "UNKNOWN";
    }

    db[MouseButtons::MOUSE_LEFT] = "MOUSE_LEFT";
    db[MouseButtons::MOUSE_MIDDLE] = "MOUSE_MIDDLE";
    db[MouseButtons::MOUSE_RIGHT] = "MOUSE_RIGHT";
    db[MouseButtons::MOUSE_X1] = "MOUSE_X1";
    db[MouseButtons::MOUSE_X2] = "MOUSE_X2";

    return db;
}
constexpr MouseButtonsReadableDb g_mouseButtonsReadable = InitMouseButtonsReadableDb();

constexpr GamepasButtonsReadableDb InitGamepadButtonsReadableDb()
{
    GamepasButtonsReadableDb db{};

    for (int i = 0; i < GamepadButtons::MAX; ++i)
    {
        db[i] = "UNKNOWN";
    }

    db[GamepadButtons::A] = "GAMEPAD_A";
    db[GamepadButtons::B] = "GAMEPAD_B";
    db[GamepadButtons::X] = "GAMEPAD_X";
    db[GamepadButtons::Y] = "GAMEPAD_Y";
    db[GamepadButtons::BACK] = "GAMEPAD_BACK";
    db[GamepadButtons::GUIDE] = "GAMEPAD_GUIDE";
    db[GamepadButtons::START] = "GAMEPAD_START";
    db[GamepadButtons::LEFTSTICK] = "GAMEPAD_LEFTSTICK";
    db[GamepadButtons::RIGHTSTICK] = "GAMEPAD_RIGHTSTICK";
    db[GamepadButtons::LEFTSHOULDER] = "GAMEPAD_LEFTSHOULDER";
    db[GamepadButtons::RIGHTSHOULDER] = "GAMEPAD_RIGHTSHOULDER";
    db[GamepadButtons::DPAD_UP] = "GAMEPAD_DPAD_UP";
    db[GamepadButtons::DPAD_DOWN] = "GAMEPAD_DPAD_DOWN";
    db[GamepadButtons::DPAD_LEFT] = "GAMEPAD_DPAD_LEFT";
    db[GamepadButtons::DPAD_RIGHT] = "GAMEPAD_DPAD_RIGHT";

    return db;
}
constexpr GamepasButtonsReadableDb g_gamepadButtonsReadable = InitGamepadButtonsReadableDb();

constexpr GamepasJoystickReadableDb InitGamepadJoystickReadableDb()
{
    GamepasJoystickReadableDb db{};

    for (int i = 0; i < GamepadJoystickAxis::AXIS_MAX; ++i)
    {
        db[i] = "UNKNOWN";
    }
    db[GamepadJoystickAxis::AXIS_LEFTX] = "AXIS_LEFTX";
    db[GamepadJoystickAxis::AXIS_LEFTY] = "AXIS_LEFTY";
    db[GamepadJoystickAxis::AXIS_RIGHTX] = "AXIS_RIGHTX";
    db[GamepadJoystickAxis::AXIS_RIGHTY] = "AXIS_RIGHTY";
    db[GamepadJoystickAxis::AXIS_TRIGGERLEFT] = "AXIS_TRIGGERLEFT";
    db[GamepadJoystickAxis::AXIS_TRIGGERRIGHT] = "AXIS_TRIGGERRIGHT";

    return db;
}
constexpr GamepasJoystickReadableDb g_gamepadJoystickAxisReadable = InitGamepadJoystickReadableDb();
}  // namespace red
