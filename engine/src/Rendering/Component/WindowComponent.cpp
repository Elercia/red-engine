#include "RedEngine/Rendering/Component/WindowComponent.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"

#include <SDL2/SDL.h>

namespace red
{
CVar<std::string> m_title{"title", "window", "RedEngine"};
CVar<int> m_height{"height", "window", 600};
CVar<int> m_width{"width", "window", 800};
CVar<FullScreenMode::Enum> m_fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};

RED_COMPONENT_BASIC_FUNCTIONS_IMPL(WindowComponent)

WindowComponent::WindowComponent(Entity* owner) : Component(owner), m_window(nullptr) {}

WindowComponent::~WindowComponent()
{
    SDL_Quit();
}

void WindowComponent::Init()
{
    //TODO Surely move this to renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        RED_LOG_ERROR("Error initializing SDL with error {}", SDL_GetError());
        SDL_Quit();
        RED_ABORT("Cannot initialize SDL2");
    }
}

void WindowComponent::CreateNewWindow()
{
    m_window = SDL_CreateWindow(m_title.GetValue().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                m_width.GetValue(), m_height.GetValue(),
                                SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (m_window == nullptr)
    {
        RED_ABORT("Error creating the windows");
    }

    RED_LOG_INFO("Created window");

    m_height->OnValueChange(
        [&](CVarValue* /*elem*/) { SDL_SetWindowSize(this->m_window, m_width.GetValue(), m_height.GetValue()); });

    m_width->OnValueChange(
        [&](CVarValue* /*elem*/) { SDL_SetWindowSize(this->m_window, m_width.GetValue(), m_height.GetValue()); });

    m_fullscreen->OnValueChange([&](CVarValue* /*elem*/) {
        int flag = 0;
        switch (m_fullscreen.GetValue())
        {
            case FullScreenMode::FULLSCREEN:
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

#ifdef RED_WINDOWS
HWND WindowComponent::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.win.window;
}
#endif

#ifdef RED_LINUX
::Window WindowComponent::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.x11.window;
}
Display* WindowComponent::GetNativeDisplay()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo();

    return sysInfo.info.x11.display;
}
#endif  // PLATFORM_LINUX

SDL_SysWMinfo WindowComponent::GetSDLSysInfo()
{
    SDL_SysWMinfo sysInfo;
    SDL_VERSION(&sysInfo.version);

    if (SDL_GetWindowWMInfo(m_window, &sysInfo) != SDL_TRUE)
    {
        RED_ERROR("Cant get native window handle on windows")
    }

    return sysInfo;
}

WindowInfo WindowComponent::GetWindowInfo() const 
{
    int width;
    int height;
    SDL_GetWindowSize(m_window, &width, &height);

    WindowInfo info{width, height};

    return info;
}

SDL_Window* WindowComponent::GetSDLWindow() { return m_window; }

}  // namespace red
