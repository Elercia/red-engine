#include <RedEngine/Core/Time/Time.hpp>
#include <RedEngine/Core/Application.hpp>
#include <RedEngine/Core/Debug/Debug.hpp>
#include <RedEngine/Core/Debug/Profiler.hpp>
#include <RedEngine/Core/Event/EventSystem.hpp>
#include <RedEngine/Core/Time/FrameCounter.hpp>

#include <array>
#include <memory>
#include <thread>

namespace red
{
Application::Application()
{
    PROFILER_APP("Main Application")
    SetLogLevel(LogLevel::LEVEL_DEBUG);
    CreateWorld();
}

Application::~Application()
{
    LoadLevelInternal(nullptr);
    delete m_world;

    PROFILER_SHUTDOWN();
}

bool Application::Run()
{
    auto* eventSystem = GetRedSubEngine<EventSystem>();

    FrameCounter fc;

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

        RED_LOG_TRACE("[Frame rate {}][Delta time {}][Time scale {}][Unscaled delta time {}]",
                      1 / Time::DeltaTime(), Time::DeltaTime(), Time::TimeScale(),
                      Time::DeltaTime(false));

        // update the world
        m_world->Update();
    }

    return true;
}

void Application::LoadLevel(const std::string& levelResource)
{
    auto* resourceEngine = GetRedSubEngine<ResourceEngine>();

    resourceEngine->LoadLevel(levelResource);
}

void Application::LoadLevelInternal(Level* level)
{
    if (m_currentLevel != nullptr)
    {
        m_currentLevel->InternFinalize();
        delete m_currentLevel;
    }

    // reset the old level
    m_currentLevel = level;

    if (level != nullptr)
        m_currentLevel->InternInit();

    m_world->Clean();
    m_world->Init();
}

red::Level* Application::GetCurrentLevel() { return m_currentLevel; }

void Application::CreateWorld()
{
    if (m_world != nullptr)
        return;

    m_world = new World;
    m_world->Init();
}

red::World* Application::GetWorld() { return m_world; }

}  // namespace red
