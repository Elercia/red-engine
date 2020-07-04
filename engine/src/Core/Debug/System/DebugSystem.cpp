
#include <RedEngine/Core/Debug/System/DebugSystem.hpp>
#include <RedEngine/Core/Debug/Component/DebugComponent.hpp>
#include <RedEngine/Core/Engine.hpp>
#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Rendering/Window.hpp>
#include <RedEngine/Core/Debug/Profiler.hpp>

namespace red
{
DebugSystem::DebugSystem(World* world)
    : System(world), m_renderingEngine(GetRedSubEngine<RenderingEngine>())
{
}

void DebugSystem::LateUpdate()
{
    PROFILER_CATEGORY("Debug", Optick::Category::Debug);

    auto* eventSystem = GetRedSubEngine<EventSystem>();
    auto* debugComp = GetSingletonEntity().GetComponent<DebugComponent>();

    if (eventSystem->GetKeyDown(KeyCodes::KEY_F))
    {
        CVar<FullScreenMode::Enum> fullscreen{"fullscreen_mode", "window",
                                              FullScreenMode::WINDOWED};

        fullscreen.ChangeValue(fullscreen.GetValue() == FullScreenMode::WINDOWED
                                   ? FullScreenMode::FULLSCREEN
                                   : FullScreenMode::WINDOWED);
    }

    if (eventSystem->GetKeyDown(KeyCodes::KEY_P))
    {
        Time::SetTimeScale(Time::TimeScale() + 0.1F);
    }

    if (eventSystem->GetKeyDown(KeyCodes::KEY_O))
    {
        Time::SetTimeScale(Time::TimeScale() - 0.1F);
    }

    // TODO add the management of the in-game console
}
}  // namespace red
