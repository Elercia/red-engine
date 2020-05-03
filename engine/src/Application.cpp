#include <array>
#include <chrono>
#include <memory>
#include <numeric>
#include <thread>
#include <RedEngine/Core/Time/Time.hpp>

#include "RedEngine/Application/Application.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Debug/Profiler.hpp"

namespace red
{
Application::Application()
{
    PROFILER_APP("Main Application")
    SetLogLevel(LogLevel::LEVEL_INFO);
}

Application::~Application() { PROFILER_SHUTDOWN(); }

bool Application::Run()
{
    RED_ASSERT(m_world != nullptr, "The application need a level to start");

    std::array<double, 10> frameTimes{};
    uint8_t frameIndex = 0;
    auto frameStartTime = std::chrono::system_clock::now();

    bool isFullScreen = false;

    // Main loop
    bool quit = false;
    while (!quit)
    {
        PROFILER_FRAME("MainThread");

        // Compute the delta time
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> diff = currentTime - frameStartTime;

        frameTimes[frameIndex] = diff.count();
        frameIndex = (frameIndex + 1u) % frameTimes.size();
        frameStartTime = currentTime;

        double deltaTime =
            std::accumulate(frameTimes.begin(), frameTimes.end(), 1., std::plus<double>()) /
            10.;  // calculate the mean of delta times (this return at least 1.f)

        RED_LOG_TRACE("Game FPS : {} delta is : {}", 1000 / deltaTime, deltaTime);

        Time::DeltaTime(deltaTime);

        // Update the inputs
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            /* handle your event here */
            switch (event.type)
            {
                case SDL_WINDOWEVENT:
                {
                    switch (event.window.event)
                    {
                        case SDL_WINDOWEVENT_CLOSE:
                            quit = true;
                            break;
                    }
                }
                break;
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_f:  // Toggle fullscreen
                            isFullScreen = !isFullScreen;
                            // TODO change this to match the configuration changes
                            //                            Configuration::GetInstance().ChangeVar<FullScreenMode::Enum>(
                            //                                "fullscreen", "window",
                            //                                isFullScreen ?
                            //                                FullScreenMode::FULLSCREEN
                            //                                             :
                            //                                             FullScreenMode::WINDOWED);
                            break;
                        case SDLK_PLUS:  // Scale the time
                            Time::TimeScale(Time::TimeScale() + 0.1);
                            break;
                        case SDLK_MINUS:  // Scale the time
                            Time::TimeScale(Time::TimeScale() - 0.1);
                            break;
                    }
                    break;
            }
        }

        // update the world
        m_world->Update();
    }

    return true;
}

void Application::CreateWorld()
{
    RED_ASSERT(m_world == nullptr, "Only one world is allowed");

    m_world = std::make_unique<World>();
}

void Application::LoadLevel(Level* level)
{
    if (m_currentLevel != nullptr)
    {
        m_currentLevel->Finalize();
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
}
World& Application::GetWorld() { return *m_world; }

}  // namespace red
