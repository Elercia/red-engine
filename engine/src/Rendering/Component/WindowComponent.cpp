#include "RedEngine/Rendering/Component/WindowComponent.hpp"

#include "RedEngine/Rendering/RenderingModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Utils/BitfieldUtils.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_video.h>

namespace red
{
CVar<std::string> WindowComponent::s_title{"title", "window", "RedEngine"};
CVar<int> WindowComponent::s_height{"height", "window", 600};
CVar<int> WindowComponent::s_width{"width", "window", 800};
CVar<FullScreenMode::Enum> WindowComponent::s_fullscreen{"fullscreen_mode", "window", FullScreenMode::WINDOWED};

WindowComponent::WindowComponent(Entity *owner) : Component(owner)
{
}

WindowComponent::~WindowComponent()
{
}

void WindowComponent::CreateNewWindow()
{
    uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;

    if (s_fullscreen == FullScreenMode::WINDOWED_FULLSCREEN)
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else if (s_fullscreen == FullScreenMode::FULLSCREEN)
    {
        windowFlags |= SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        windowFlags |= SDL_WINDOW_RESIZABLE;
    }

    m_window = SDL_CreateWindow(s_title.GetValue().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                s_width.GetValue(), s_height.GetValue(), windowFlags);

    if (m_window == nullptr)
    {
        RedAbort("Error creating the windows");
    }

    RED_LOG_INFO("Created window");
}

#if 0
#ifdef RED_WINDOWS
HWND WindowComponent::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo(m_window);

    return sysInfo.info.win.window;
}
#endif

#ifdef RED_LINUX
::Window WindowComponent::GetNativeHandle()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo(m_window);

    return sysInfo.info.x11.window;
}
Display *WindowComponent::GetNativeDisplay()
{
    SDL_SysWMinfo sysInfo = GetSDLSysInfo(m_window);

    return sysInfo.info.x11.display;
}
#endif  // PLATFORM_LINUX


static SDL_SysWMinfo GetSDLSysInfo(SDL_Window *window)
{
    SDL_SysWMinfo sysInfo;
    SDL_VERSION(&sysInfo.version);

    if (SDL_GetWindowWMInfo(window, &sysInfo) != SDL_TRUE)
    {
        RedError("Cant get native window handle on windows")
    }

    return sysInfo;
}
#endif

WindowInfo WindowComponent::GetWindowInfo() const
{
    int width;
    int height;
    SDL_GetWindowSize(m_window, &width, &height);
    uint32 windowFlags = SDL_GetWindowFlags(m_window);

    FullScreenMode::Enum mode = FullScreenMode::WINDOWED;

    if (HasBit(windowFlags, SDL_WINDOW_FULLSCREEN))
    {
        mode = FullScreenMode::FULLSCREEN;
    }
    else if (HasBit(windowFlags, SDL_WINDOW_FULLSCREEN_DESKTOP))
    {
        mode = FullScreenMode::WINDOWED_FULLSCREEN;
    }

    WindowInfo info{width, height, mode};

    return info;
}

SDL_Window *WindowComponent::GetSDLWindow()
{
    return m_window;
}

template <>
std::string Serialize(const FullScreenMode::Enum &typeValue)
{
    switch (typeValue)
    {
        case FullScreenMode::FULLSCREEN:
            return "0";
        case FullScreenMode::WINDOWED_FULLSCREEN:
            return "1";
        default:
            return "2";
    }
}

template <>
bool Deserialize(FullScreenMode::Enum &typeValue, const std::string &stringValue)
{
    if (stringValue == "0")
    {
        typeValue = FullScreenMode::FULLSCREEN;
        return true;
    }
    if (stringValue == "1")
    {
        typeValue = FullScreenMode::WINDOWED_FULLSCREEN;
        return true;
    }
    if (stringValue == "2")
    {
        typeValue = FullScreenMode::WINDOWED;
        return true;
    }

    return false;
}

}  // namespace red
