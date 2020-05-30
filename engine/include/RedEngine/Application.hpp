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

    Application(const Application&) = delete;
    Application(Application&&) = default;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = default;

    World& CreateWorld();

    bool Run();

private:
    std::unique_ptr<World> m_world;
};
}  // namespace red
