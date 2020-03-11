#include <RedEngine/Application.hpp>
#include <RedEngine/Engine.hpp>
#include <RedEngine/debug/Debug.hpp>
#include <RedEngine/ecs/World.hpp>
#include <RedEngine/systems/RenderingSystem.hpp>

#include <array>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <thread>
#include <memory>

namespace red
{

Application::Application() : m_config(), m_world(nullptr), m_window(nullptr) {}

Application::~Application() {}

void Application::InitFromCommandLine(int argc, char* argv[])
{
    m_config.InitFromCommandLine(argc, argv);
}

void Application::InitFromCommandLine(char* /*cmdLine*/)
{ /* TODO */
}

bool Application::Run()
{
    RED_ASSERT(m_world != nullptr, "At least one world is required");

    std::array<float, 10> frameTimes{};
    uint8_t frameIndex = 0;
    auto frameStartTime = std::chrono::system_clock::now();
    const auto startTime = std::chrono::system_clock::now();

    // Main loop
    while (true)
    {
        // Compute the delta time
        auto currentTime = std::chrono::system_clock::now();
        std::chrono::duration<float, std::milli> diff = currentTime - frameStartTime;

        frameTimes[frameIndex] = diff.count();
        frameIndex = (frameIndex + 1u) % frameTimes.size();
        frameStartTime = currentTime;

        float deltaTime =
            std::accumulate(frameTimes.begin(), frameTimes.end(), 1.f, std::plus<float>()) /
            10.f; // calculate the mean of delta times (this return at least 1.f)

        //
        // std::cout << "Game FPS : " << 1000 / deltaTime << " delta is : " << deltaTime <<
        // std::endl;

        // Update the inputs

        // update the world
        m_world->Update(deltaTime);

        // let the program run for 10 seconds
        std::chrono::duration<float> loopDuration = currentTime - startTime;
        if (loopDuration.count() > 10.f) { break; }
    }

    return true;
}

std::shared_ptr<World> red::Application::CreateWorld(bool registerConfiguredSystems)
{
    RED_ASSERT(m_world == nullptr, "Only one world is allowed");

    m_world = std::make_shared<World>();

    if (registerConfiguredSystems) { m_world->AddSystem<RenderingSystem>(); }

    return m_world;
}

Window& Application::InitWindow(const std::string& title)
{
    RED_ASSERT(m_window == nullptr, "Only one window is allowed");

    m_window = std::make_unique<red::Window>(title);

    RenderingEngine& renderingEngine = GetRedInstance().GetRenderingEngine();

    renderingEngine.InitializeEngine(m_window.get());

    return *m_window;
}

} // namespace red
