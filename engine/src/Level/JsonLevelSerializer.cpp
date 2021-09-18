#include "RedEngine/Level/JsonLevelSerializer.hpp"

#include "RedEngine/Level/JsonLevelNames.hpp"

namespace red
{
JsonLevelSerializer::JsonLevelSerializer(const Level* level) : ILevelSerializer(level)
{
}

std::string JsonLevelSerializer::SerializeData(const LevelData& levelData)
{
    json levelJson;

    levelJson[JsonNames::LEVEL_ENTITIES] = {};

    for (auto entityData : levelData.m_entities)
    {
        levelJson[JsonNames::LEVEL_ENTITIES].push_back(SerializeEntity(entityData));
    }

    return levelJson.dump(1, '\t');
}

JsonLevelSerializer::json JsonLevelSerializer::SerializeEntity(const EntityData& entityData)
{
    json entityJson;

    entityJson[JsonNames::ENTITY_ID] = entityData.m_id;
    entityJson[JsonNames::ENTITY_NAME] = entityData.m_name;

    entityJson[JsonNames::ENTITY_CHILDREN] = json::array();
    for (auto& childData : entityData.m_children)
    {
        entityJson[JsonNames::ENTITY_CHILDREN].push_back(SerializeEntity(childData));
    }

    json componentsJson = json::object();
    for (auto& component : entityData.m_components)
    {
        componentsJson[component.first] = SerializeComponent(component.second);
    }
    entityJson[JsonNames::ENTITY_COMPONENTS] = componentsJson;

    return entityJson;
}

JsonLevelSerializer::json JsonLevelSerializer::SerializeComponent(const ComponentData& componentData)
{
    json componentJson = json::object();

    for (auto& member : componentData.m_serializedMembers)
    {
        componentJson[member.key] = member.value;
    }

    return componentJson;
}
}  // namespace red
