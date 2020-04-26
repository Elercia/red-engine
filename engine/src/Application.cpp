#include <array>
#include <chrono>
#include <memory>
#include <numeric>
#include <thread>

#include "RedEngine/Application/Application.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Debug/Debug.hpp"
#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Rendering/RenderingSystem.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Debug/Profiler.hpp"

namespace red
{
Application::Application() : m_world(nullptr)
{
    PROFILER_APP("Main Application")
    SetLogLevel(LogLevel::LEVEL_INFO);
}

Application::~Application() { PROFILER_SHUTDOWN(); }

bool Application::Run()
{
    RED_ASSERT(m_world != nullptr, "At least one world is required");

    std::array<float, 10> frameTimes{};
    uint8_t frameIndex = 0;
    auto frameStartTime = std::chrono::system_clock::now();
    const auto startTime = std::chrono::system_clock::now();

    bool isFullScreen = false;

    // Main loop
    bool quit = false;
    while (!quit)
    {
        PROFILER_FRAME("MainThread");

        // Compute the delta time
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float, std::milli> diff = currentTime - frameStartTime;

        frameTimes[frameIndex] = diff.count();
        frameIndex = (frameIndex + 1u) % frameTimes.size();
        frameStartTime = currentTime;

        float deltaTime =
            std::accumulate(frameTimes.begin(), frameTimes.end(), 1.f, std::plus<float>()) /
            10.f;  // calculate the mean of delta times (this return at least 1.f)

        RED_LOG_TRACE("Game FPS : {} delta is : {}", 1000 / deltaTime, deltaTime);

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
                        case SDLK_f:
                            isFullScreen = !isFullScreen;
                            Configuration::GetInstance().ChangeVar<FullScreenMode::Enum>(
                                "fullscreen", "window",
                                isFullScreen ? FullScreenMode::FULLSCREEN
                                             : FullScreenMode::WINDOWED);
                            break;
                    }
                    break;
            }
        }

        // update the world
        m_world->Update(deltaTime);
    }

    return true;
}

World& Application::CreateWorld(bool registerConfiguredSystems)
{
    RED_ASSERT(m_world == nullptr, "Only one world is allowed");

    m_world = std::make_unique<World>();

    if (registerConfiguredSystems)
    {
        m_world->AddSystem<RenderingSystem>();
    }

    return *m_world;
}

void Application::LoadLevel(std::string_view name) {}

}  // namespace red
