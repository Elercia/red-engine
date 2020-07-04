#pragma once

#include <memory>
#include <stack>

#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Rendering/Window.hpp"

namespace red
{
class Application : public Uncopyable
{
    friend class Engine;

public:
    explicit Application();
    ~Application();

    bool Run();

    void CreateWorld();

    /// Load a level from the class named LevelType
    template <class LevelType>
    void LoadLevel();

    /// Load a anonymous level as described in the levelResource file
    void LoadLevel(const std::string& levelResource);

    World& GetWorld();

private:
    /// Properly load a level
    void LoadLevel(std::unique_ptr<Level>&& level);

private:
    std::unique_ptr<World> m_world{nullptr};
    std::unique_ptr<Level> m_currentLevel{nullptr};
};
}  // namespace red

#include "inl/Application.inl"
