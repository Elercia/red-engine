
#include <RedEngine/Engine.hpp>
#include <RedEngine/Window.hpp>
#include <RedEngine/debug/Debug.hpp>

namespace red
{
namespace internal
{
    SDL2Initializer::SDL2Initializer()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            RED_ABORT("Error")
        }
    }
    SDL2Initializer::~SDL2Initializer() { SDL_Quit(); }
}  // namespace internal

Window::Window(std::string title) : m_title(std::move(title))
{
    m_window = SDL_CreateWindow(m_title.c_str(), 100, 100, 800, 600, SDL_WINDOW_SHOWN);

    if (m_window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        RED_ABORT("Error")
    }
}

Window::~Window() { SDL_DestroyWindow(m_window); }

#ifdef PLATFORM_WIN32
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
