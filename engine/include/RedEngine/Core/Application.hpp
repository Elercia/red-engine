#pragma once

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/Window.hpp"

#include <memory>
#include <stack>

namespace red
{
class Application : public Uncopyable
{
    friend class Engine;

public:
    explicit Application();
    ~Application();

    bool Run();

    /// Load a level from the class named LevelType
    template <class LevelType>
    void LoadLevel();

    /// Load a anonymous level as described in the levelResource file
    void LoadLevel(const std::string& levelResource);

    std::shared_ptr<Level> GetCurrentLevel();

    void CreateWorld();
    World* GetWorld();

private:
    /// Properly load a level
    void LoadLevelInternal(Level* level);

private:
    std::shared_ptr<Level> m_currentLevel{nullptr};
    World* m_world{nullptr};
};
}  // namespace red

#include "inl/Application.inl"
