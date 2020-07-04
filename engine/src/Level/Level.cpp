#include <RedEngine/Level/Level.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Rendering/System/RenderingSystem.hpp>

namespace red
{
Level::Level(const char* name, World* world) : m_levelName(name), m_world(world) {}
void Level::SetWorld(World* world) {m_world = world;}

}  // namespace red