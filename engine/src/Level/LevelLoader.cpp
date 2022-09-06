#include "RedEngine/Level/LevelLoader.hpp"

#include "RedEngine/Level/LevelModule.hpp"

#include "RedEngine/Level/Level.hpp"

namespace red
{
LevelLoader::LevelLoader(World* world) : m_world(world)
{
}

LevelLoader::~LevelLoader()
{
}

Level* LevelLoader::LoadLevel(const Path& path)
{
    LevelData levelData = ReadLevelData(path);

    return ParseLevelData(levelData);
}

Level* LevelLoader::ParseLevelData(const LevelData& levelData)
{
    Level* level = new Level("deserializedLevel", m_world);
    level->SetState(Level::State::Loading);
    level->InternInit();

    for (auto& entityData : levelData.m_entities)
    {
        CreateEntity(level, entityData);
    }

    level->SetState(Level::State::Ready);

    return level;
}

void LevelLoader::CreateEntity(Level* level, const EntityData& entityData, Entity* parent /*= nullptr*/)
{
    Entity* entity = level->CreateEntity(entityData.m_id, entityData.m_name, parent);

    for (auto& childData : entityData.m_children)
    {
        CreateEntity(level, childData, entity);
    }

    for (auto& componentDataIt : entityData.m_components)
    {
        CreateComponent(componentDataIt.second, entity);
    }
}

void LevelLoader::CreateComponent(const ComponentData& componentData, Entity* owner)
{
    const auto* compRegistry = m_world->GetComponentRegistry();

    TypeTraits typeTraits = GetTypeInfoFromTypeName(componentData.m_name);
    const auto* compTypeTraits = compRegistry->GetComponentTraits(typeTraits.typeId);

    if (compTypeTraits == nullptr)
    {
        RED_LOG_ERROR("Deserializing a unknown component {}", componentData.m_name);
        return;
    }

    Component* comp = owner->AddComponent(componentData.m_name);

    for (auto& [memberName, memberString] : componentData.m_serializedMembers)
    {
        auto memberTraitsIt = compTypeTraits->members.find(memberName);

        if (memberTraitsIt == compTypeTraits->members.end())
        {
            RED_LOG_ERROR("Deserializing a unknown component member {}::{}", componentData.m_name, memberName);
            continue;
        }

        memberTraitsIt->second.deserializationFunction(comp, memberString);
    }
}
}  // namespace red
