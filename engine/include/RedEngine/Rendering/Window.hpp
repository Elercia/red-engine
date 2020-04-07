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
    Display *GetNativeDisplay();
#endif

    WindowInfo GetWindowInfo();

private:
    SDL_SysWMinfo GetSDLSysInfo();

    std::string m_title;
    SDL_Window *m_window;

    CVar<int> m_height{"height", 800, "window"};
    CVar<int> m_width{"width", 600, "window"};
    CVar<FullScreenMode::Enum> m_fullscreen{"fullscreen", FullScreenMode::WINDOWED, "window"};
};

}  // namespace red

// Fixme Maybe add this into a macro
//  This is used to be able to add a Enum into a CVar
template <class E>
struct enum_traits
{
    friend std::istream &operator>>(std::istream &is, E &e)
    {
        long i;  // or intmax_t, whatever
        std::istream &r = is >> i;
        e = E(i);
        return r;
    }
};
template class enum_traits<red::FullScreenMode::Enum>;

std::istream &operator>>(std::istream &, red::FullScreenMode::Enum &);
