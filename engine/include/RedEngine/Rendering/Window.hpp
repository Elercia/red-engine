#pragma once

#include "../Core/Configuration/CVar.hpp"

#include "RedEngine/RedEngineBase.hpp"

#include <SDL2/SDL.h>
#include <SDL_syswm.h>
#include <string>

namespace red
{
struct FullScreenMode
{
    enum Enum : uint8_t
    {
        FULLSCREEN = 0,
        BORDER_LESS = 1,
        WINDOWED = 2
    };
};

RED_NEW_CONFIG_TYPE_SERIALIZATOR(FullScreenMode::Enum)
{
    switch (typeValue)
    {
        case FullScreenMode::FULLSCREEN:
            return "0";
        case FullScreenMode::BORDER_LESS:
            return "1";
        default:
            return "2";
    }
}
RED_NEW_CONFIG_TYPE_DESERIALIZATOR(FullScreenMode::Enum)
{
    if (stringValue == "0")
    {
        typeValue = FullScreenMode::FULLSCREEN;
    }
    else if (stringValue == "1")
    {
        typeValue = FullScreenMode::BORDER_LESS;
    }
    else
    {
        typeValue = FullScreenMode::WINDOWED;
    }
}

struct WindowInfo
{
    int width;
    int height;
};

class Window
{
public:
    explicit Window();
    ~Window();

#ifdef PLATFORM_WINDOWS
    HWND GetNativeHandle();
#endif

#ifdef PLATFORM_LINUX
    ::Window GetNativeHandle();
    Display *GetNativeDisplay();
#endif

    WindowInfo GetWindowInfo();

    SDL_Window *GetSDLWindow();

    static Window &GetWindow();

private:
    SDL_SysWMinfo GetSDLSysInfo();

    std::string m_title{"Hello Red-Engine"};
    SDL_Window *m_window;

    CVar<int> m_height{"height", "window", 600};
    CVar<int> m_width{"width", "window", 800};
    CVar<FullScreenMode::Enum> m_fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};
};

}  // namespace red