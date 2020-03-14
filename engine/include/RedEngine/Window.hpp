#pragma once

#include <SDL2/SDL.h>
#include <SDL_syswm.h>

#include <string>

namespace red
{
namespace internal
{
    class SDL2Initializer
    {
    public:
        SDL2Initializer();
        ~SDL2Initializer();

    private:
        static SDL2Initializer ms_instance;
    };
}  // namespace internal

class Window
{
public:
    explicit Window(std::string title);
    ~Window();

#ifdef PLATFORM_WIN32
    HWND GetNativeHandle();
#endif

#ifdef PLATFORM_LINUX
    ::Window GetNativeHandle();
    Display* GetNativeDisplay();
#endif

private:
    SDL_SysWMinfo GetSDLSysInfo();

    std::string m_title;
    SDL_Window* m_window;
};

}  // namespace red
