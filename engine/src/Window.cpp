#include <RedEngine/Window.hpp>
#include <RedEngine/debug/Debug.hpp>
#include <iostream>

namespace red
{
namespace internal
{
    SDL2Initializer::SDL2Initializer() {}
    SDL2Initializer::~SDL2Initializer() {}
}  // namespace internal

Window::Window(std::string title) : m_title(std::move(title))
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        RED_ABORT("Error")
    }

    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                800, 600, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        RED_ABORT("Error")
    }
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }

    SDL_Quit();
}

#ifdef PLATFORM_WINDOWS
HWND Window::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.win.window;
}
#endif

#ifdef PLATFORM_LINUX
::Window Window::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.x11.window;
}
Display* Window::GetNativeDisplay()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.x11.display;
}
#endif

SDL_SysWMinfo Window::GetSDLSysInfo()
{
    SDL_SysWMinfo sysInfo;
    SDL_VERSION(&sysInfo.version);

    if (!SDL_GetWindowWMInfo(m_window, &sysInfo))
    {
        RED_ERROR("Cant get native window handle on windows")
    }

    return sysInfo;
}
}  // namespace red
