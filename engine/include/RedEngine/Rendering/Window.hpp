#pragma once

#include <SDL2/SDL.h>
#include <SDL_syswm.h>

#include <string>

namespace red
{
struct WindowInfo
{
    int width;
    int height;
};

class Window
{
public:
    explicit Window(std::string title);
    ~Window();

#ifdef PLATFORM_WINDOWS
    HWND GetNativeHandle();
#endif

#ifdef PLATFORM_LINUX
    ::Window GetNativeHandle();
    Display* GetNativeDisplay();
#endif

    WindowInfo GetWindowInfo();

private:
    SDL_SysWMinfo GetSDLSysInfo();

    std::string m_title;
    SDL_Window* m_window;
};

}  // namespace red
