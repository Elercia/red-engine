#pragma once

#include <memory>
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Rendering/Window.hpp"

namespace red
{
class World;

class Application : public Uncopyable
{
public:
    Application();
    ~Application();

    bool Run();

    template <class LevelType>
    void LoadLevel();

private:
    std::unique_ptr<Level> m_level;
};
}  // namespace red

#include "inl/Application.inl"
