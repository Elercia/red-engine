#include <RedEngine/Level/Level.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>

namespace red
{
Level::Level(const char *name) : m_levelName(name) {}

void Level::CreateWorld(bool registerDefaultSystems)
{
    RED_ASSERT(m_world == nullptr, "Only one world is allowed");

    m_world = std::make_unique<World>();

    if (registerDefaultSystems)
    {
        m_world->AddSystem<RenderingSystem>();
    }
}
void Level::Update() { m_world->Update(); }
}  // namespace red