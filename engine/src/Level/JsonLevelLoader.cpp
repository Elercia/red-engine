#include "RedEngine/Level/JsonLevelLoader.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/JsonLevelNames.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

namespace red
{
JsonLevelLoader::JsonLevelLoader(World* world) : LevelLoader(world)
{
}

JsonLevelLoader::~JsonLevelLoader()
{
}

LevelData JsonLevelLoader::ReadLevelData(const Path& path)
{
    LevelData levelData;

    std::string str = ReadFile(path);
    json jsonLevel = json::parse(str);

    for (auto& jsonEntityData : jsonLevel[JsonNames::LEVEL_ENTITIES])
    {
        EntityData entityData = ParseEntity(jsonEntityData);

        levelData.m_entities.push_back(entityData);
    }

    return levelData;
}

ComponentData JsonLevelLoader::ParseComponent(const std::string& componentName, json componentJson)
{
    ComponentData componentData;
    componentData.m_name = componentName;

    for (auto& [memberName, memberValue] : componentJson.items())
    {
        if (!memberValue.is_string())
        {
            RED_LOG_ERROR("JsonLevelLoader::ParseComponent : {}::{} is not a string", componentName, memberName);
            continue;
        }

        componentData.m_serializedMembers.push_back({memberName, memberValue});
    }

    return componentData;
}

EntityData JsonLevelLoader::ParseEntity(json jsonEntityData)
{
    EntityData entityData;

    entityData.m_name = jsonEntityData[JsonNames::ENTITY_NAME];
    entityData.m_id = jsonEntityData[JsonNames::ENTITY_ID];

    for (auto& childJson : jsonEntityData[JsonNames::ENTITY_CHILDREN])
    {
        EntityData childData = ParseEntity(childJson);

        entityData.m_children.push_back(childData);
    }

    for (auto& [componentName, componentJson] : jsonEntityData[JsonNames::ENTITY_COMPONENTS].items())
    {
        ComponentData componentData = ParseComponent(componentName, componentJson);

        entityData.m_components.insert({componentName, componentData});
    }

    return entityData;
}
}  // namespace red
