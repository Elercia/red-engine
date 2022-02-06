#pragma once

#include "RedEngine/Core/Configuration/CVar.hpp"
#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/SerializationFunction.hpp"

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

RED_COMPONENT_BASIC_FUNCTIONS_DECLARATION(WindowComponent)

class WindowComponent : public Component
{
public:
    RED_START_COMPONENT_REGISTER_INHERITHED(WindowComponent, Component)
    RED_END_COMPONENT_REGISTER()

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
    SDL_Window* m_window;
};

template <>
std::string Serialize(const FullScreenMode::Enum& typeValue);

template <>
bool Deserialize(FullScreenMode::Enum& typeValue, const std::string& stringValue);
}  // namespace red