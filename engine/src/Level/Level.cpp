#include "RedEngine/Level/Level.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <memory>

namespace red
{
Level::Level(std::string name, World* world)
    : IResource(Path::Resource(name), ResourceType::LEVEL)
    , m_levelName(std::move(name))
    , m_world(world)
    , m_rootEntity(nullptr)
{
}

void Level::InternInit()
{
    m_rootEntity = m_world->CreateRootEntity(this);
    Init();
}

void Level::InternFinalize()
{
    Finalize();
    m_rootEntity->Destroy();
}

const std::string& Level::GetName() const { return m_levelName; }

red::Entity* Level::CreateEntity() { return m_world->CreateEntity(m_rootEntity); }

red::Entity* Level::CreateEntity(const std::string& name) { return m_world->CreateEntity(name, m_rootEntity); }

red::Entity* Level::GetRootEntity() { return m_rootEntity; }

}  // namespace red