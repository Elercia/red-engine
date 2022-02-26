#pragma once

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"

#include <SDL2/SDL_syswm.h>

struct SDL_Window;

namespace red
{
struct FullScreenMode
{
    enum Enum : uint8_t
    {
        FULLSCREEN = 0,
        WINDOWED_FULLSCREEN = 1,
        WINDOWED = 2
    };
};

struct WindowInfo
{
    int width;
    int height;
    FullScreenMode::Enum fullscreenMode;
};

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(WindowComponent)

class WindowComponent : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(WindowComponent, Component)
    RED_END_COMPONENT_REGISTER()

    static CVar<std::string> s_title;
    static CVar<int> s_height;
    static CVar<int> s_width;
    static CVar<FullScreenMode::Enum> s_fullscreen;

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
    
    void CreateNewWindow();

private:
    SDL_SysWMinfo GetSDLSysInfo();

private:
    SDL_Window* m_window{nullptr};
};

template <>
std::string Serialize(const FullScreenMode::Enum& typeValue);

template <>
bool Deserialize(FullScreenMode::Enum& typeValue, const std::string& stringValue);
}  // namespace red