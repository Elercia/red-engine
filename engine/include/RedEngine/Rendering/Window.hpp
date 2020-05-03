#pragma once

#include <SDL2/SDL.h>
#include <SDL_syswm.h>

#include "../Core/Configuration/CVar.hpp"

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

RED_NEW_CONFIG_TYPE_SERIALIZATOR(FullScreenMode::Enum) { return ""; }
RED_NEW_CONFIG_TYPE_DESERIALIZATOR(FullScreenMode::Enum) { typeValue = FullScreenMode::FULLSCREEN; }

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

private:
    SDL_SysWMinfo GetSDLSysInfo();

    std::string m_title{"Hello Red-Engine"};
    SDL_Window *m_window;

    CVar<int> m_height{"height", "window", 600};
    CVar<int> m_width{"width", "window", 800};
    CVar<FullScreenMode::Enum> m_fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};
};

}  // namespace red