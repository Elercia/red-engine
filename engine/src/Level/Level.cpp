#include "RedEngine/Level/Level.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/JsonLevelData.hpp"
#include "RedEngine/Level/JsonLevelSerializer.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <fstream>
#include <iosfwd>
#include <memory>

namespace red
{
Level::Level(std::string name, World* world)
    : IResource("", ResourceType::LEVEL), m_levelName(std::move(name)), m_world(world), m_rootEntity(nullptr)
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

const std::string& Level::GetName() const
{
    return m_levelName;
}

red::Entity* Level::CreateEntity()
{
    return m_world->CreateEntity(m_rootEntity);
}

red::Entity* Level::CreateEntity(const std::string& name)
{
    return m_world->CreateEntity(name, m_rootEntity);
}

red::Entity* Level::CreateEntity(EntityId id, const std::string& name)
{
    return m_world->CreateEntity(id, name, m_rootEntity);
}

red::Entity* Level::CreateEntity(EntityId id, const std::string& name, Entity* parent)
{
    return m_world->CreateEntity(id, name, parent);
}

red::Entity* Level::GetRootEntity()
{
    return m_rootEntity;
}

void Level::Serialize(const std::string& path)  // TODO Make const
{
    JsonLevelSerializer serializer(this);

    if (serializer.SerializeToFile(path) == false)
        RED_LOG_ERROR("Failed to serialize level to \"{}\"", path);
}

void Level::Deserialize(const std::string& path)
{
    JsonLevelSerializer serializer(this);

    if (serializer.DeserializeFromFile(path) == false)
        RED_LOG_ERROR("Failed to load level from \"{}\"", path);
}

}  // namespace red