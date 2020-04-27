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
public:
    Application();
    ~Application();

    bool Run();

    void CreateWorld();

    template <class LevelType>
    void LoadLevel();

    World& GetWorld();

private:
    void LoadLevel(Level* level);

    std::unique_ptr<World> m_world{nullptr};
    std::unique_ptr<Level> m_currentLevel{nullptr};
};
}  // namespace red

#include "inl/Application.inl"
