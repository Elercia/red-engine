#include "RedEngine/Level/Level.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/JsonLevelData.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <fstream>
#include <iostream>
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

red::Entity* Level::GetRootEntity()
{
    return m_rootEntity;
}

void Level::Serialize(const std::string& path) const
{
    JsonLevelData levelData;

    for (auto* entities : m_rootEntity->GetChildren())
    {
        entities->Serialize(levelData.AddLevelEntityData());
    }

    std::string levelStr = levelData.m_levelObject.dump(4);

    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::ostream os(&fb);
    os << levelStr;
    fb.close();
}

void Level::Deserialize(const std::string& path)
{
    std::string levelStr;
    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::istream os(&fb);
    os >> levelStr;
    fb.close();

    JsonLevelData levelData;
    levelData.m_levelObject = json::parse(levelStr);
}

}  // namespace red