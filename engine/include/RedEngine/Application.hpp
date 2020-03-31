#pragma once

#include <memory>

#include "Core/Engine.hpp"
#include "Rendering/Window.hpp"

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

    World& CreateWorld(bool registerConfiguredSystems = true);

    bool Run();

private:
    std::unique_ptr<World> m_world;
};
}  // namespace red
