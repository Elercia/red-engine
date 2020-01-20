#pragma once

#include <RedEngine/Configuration.hpp>
#include <RedEngine/Engine.hpp>
#include <RedEngine/Window.hpp>

#include <memory>

namespace red
{

class World;

class Application
{
public:
    Application(int argc = 0, char* argv[] = nullptr);
    ~Application();

    std::shared_ptr<World> CreateWorld(bool registerConfiguredSystems = true);

    std::shared_ptr<Window> CreateWindow();

    bool Run();

private:
    Configuration m_config;
    std::shared_ptr<World> m_world;
    std::shared_ptr<Window> m_window;
};
} // namespace red
