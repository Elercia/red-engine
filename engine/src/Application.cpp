#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Application/Application.hpp>
#include <RedEngine/Debug/Debug.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>
#include <RedEngine/Debug/Profiler.hpp>
#include <RedEngine/Input/Component/UserInput.hpp>
#include <RedEngine/Event/EventSystem.hpp>

#include <array>
#include <memory>
#include <thread>
#include <RedEngine/Core/Time/FrameCounter.hpp>

namespace red
{
Application::Application()
{
    PROFILER_APP("Main Application")
    SetLogLevel(LogLevel::LEVEL_DEBUG);
}

Application::~Application() { PROFILER_SHUTDOWN(); }

bool Application::Run()
{
    RED_ASSERT(m_world != nullptr, "The application need a level to start");
    auto* eventSystem = GetRedSubEngine<EventSystem>();

    FrameCounter fc;

    bool isFullScreen = false;

    // Main loop
    while (true)
    {
        PROFILER_FRAME("MainThread");

        // Compute the delta time
        auto deltaTime = fc.Update();

        Time::SetDeltaTime(deltaTime);

        eventSystem->Update();

        if (eventSystem->QuitRequested())
        {
            break;
        }

        if (eventSystem->GetKeyDown(KeyCodes::KEY_F))
        {
            isFullScreen = !isFullScreen;
            CVar<FullScreenMode::Enum> fullscreen{"fullscreen_mode", "window",
                                                  FullScreenMode::WINDOWED};
            fullscreen.ChangeValue(isFullScreen ? FullScreenMode::FULLSCREEN
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

        RED_LOG_TRACE("[Frame rate {}][Delta time {}][Time scale {}][Unscaled delta time {}]",
                      1 / Time::DeltaTime(), Time::DeltaTime(), Time::TimeScale(),
                      Time::DeltaTime(false));

        // update the world
        m_world->Update();
    }

    return true;
}

void Application::CreateWorld()
{
    RED_ASSERT(m_world == nullptr, "Only one world is allowed");

    m_world = std::make_unique<World>();

    auto entity = m_world->CreateSingletonEntity();
    entity->AddComponent<UserInputComponent>();
}

void Application::LoadLevel(Level* level)
{
    if (m_currentLevel != nullptr)
    {
        m_currentLevel->Finalize(*m_world);
    }

    // reset the old level
    m_currentLevel.reset(level);

    if (m_world == nullptr)
    {
        CreateWorld();
    }

    m_world->UnloadSystems();
    m_world->UnloadTransientEntities();

    m_currentLevel->Init(*m_world);

    m_world->Init();
}
World& Application::GetWorld() { return *m_world; }

}  // namespace red
