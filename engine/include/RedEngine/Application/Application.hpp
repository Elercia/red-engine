#pragma once

#include <memory>

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Rendering/Window.hpp"

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

    World& CreateWorld(bool registerConfiguredSystems = true);

    bool Run();

    template <class LevelType>
    void LoadLevel();

    void LoadLevel(std::string_view name);

private:
    std::unique_ptr<World> m_world;
};
}  // namespace red

#include "inl/Application.inl"
