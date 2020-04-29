#include <RedEngine/Debug/Debug.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <iostream>
#include <RedEngine/Debug/Logger/Logger.hpp>

namespace red
{
Window::Window() : m_title("Hello Red-Engine")
{
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width.GetValue(), m_height.GetValue(),
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (m_window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        RED_ABORT("Error")
    }

    RED_LOG_INFO("Create new window");

    m_height.RegisterChangeCallback([&](CVarValue<int>* /*elem*/) {
        SDL_SetWindowSize(this->m_window, m_width.GetValue(), m_height.GetValue());
    });

    m_width.RegisterChangeCallback([&](CVarValue<int>* /*elem*/) {
        SDL_SetWindowSize(this->m_window, m_width.GetValue(), m_height.GetValue());
    });

    m_fullscreen.RegisterChangeCallback([&](CVarValue<FullScreenMode::Enum>* elem) {
        int flag = 0;
        switch (elem->GetValue())
        {
            case FullScreenMode::FULLSCREEN:
                flag = SDL_WINDOW_FULLSCREEN;
                break;
            case FullScreenMode::BORDER_LESS:
                flag = SDL_WINDOW_FULLSCREEN;
                break;
            case FullScreenMode::WINDOWED:
                flag = 0;
                break;
        }

        SDL_SetWindowFullscreen(this->m_window, flag);
    });
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
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

WindowInfo Window::GetWindowInfo()
{
    WindowInfo info{};
    SDL_GetWindowSize(m_window, &info.width, &info.height);

    return info;
}
SDL_Window* Window::GetSDLWindow() { return m_window; }
}  // namespace red
