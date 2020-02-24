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
    Application();
    ~Application();

    void InitFromCommandLine(int argc, char* argv[]);
    void InitFromCommandLine(char* cmdLine);

    std::shared_ptr<World> CreateWorld(bool registerConfiguredSystems = true);

    Window& InitWindow(std::wstring title);

    bool Run();

private:
    Configuration m_config;
    std::shared_ptr<World> m_world;
    std::unique_ptr<Window> m_window;
};
} // namespace red
