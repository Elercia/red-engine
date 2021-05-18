#pragma once

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Configuration/CVarSerialization.hpp"

struct SDL_Window;
#include <SDL2/SDL_syswm.h>

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

class WindowComponent : public Component
{
public:
    WindowComponent(Entity* owner);
    virtual ~WindowComponent();

#ifdef RED_WINDOWS
    HWND GetNativeHandle();
#endif

#ifdef RED_LINUX
    ::Window GetNativeHandle();
    Display* GetNativeDisplay();
#endif

    WindowInfo GetWindowInfo() const;

    SDL_Window* GetSDLWindow();

    void Init();
    void CreateNewWindow();

private:
    SDL_SysWMinfo GetSDLSysInfo();

private:
    SDL_Window* m_window;
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
}  // namespace red