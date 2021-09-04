#include "RedEngine/Level/JsonLevelSerializer.hpp"

namespace red
{
JsonLevelSerializer::JsonLevelSerializer(const Level* level) : ILevelSerializer(level)
{
}

std::string JsonLevelSerializer::SerializeData(const LevelData& levelData)
{
    json levelJson;

    levelJson[LEVEL_ENTITIES] = {};

    for (auto entityData : levelData.m_entities)
    {
        levelJson[LEVEL_ENTITIES].push_back(SerializeEntity(entityData));
    }

    return levelJson.dump(1, '\t');
}

JsonLevelSerializer::json JsonLevelSerializer::SerializeEntity(const EntityData& entityData)
{
    json entityJson;

    entityJson[ENTITY_ID] = entityData.m_id;
    entityJson[ENTITY_NAME] = entityData.m_name;

    entityJson[ENTITY_CHILDREN] = json::array();
    for (auto& childData : entityData.m_children)
    {
        entityJson[LEVEL_ENTITIES].push_back(SerializeEntity(childData));
    }

    json componentsJson = json::object();
    for (auto& component : entityData.m_components)
    {
        componentsJson[component.first] = SerializeComponent(component.second);
    }
    entityJson[ENTITY_COMPONENTS] = componentsJson;

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

/*
bool JsonLevelSerializer::SerializeToFile(const std::string& path)
{
    bool status = true;

    JsonLevelData levelData;

    for (auto* entity : m_level->m_rootEntity->GetChildren())
    {
        status = SerializeEntity(entity, levelData.AddLevelEntityData()) && status;
    }

    std::string levelStr = levelData.m_levelObject.dump(4);

    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::ostream os(&fb);
    os << levelStr;
    fb.close();

    return status;
}

bool JsonLevelSerializer::DeserializeFromFile(const std::string& path)
{
    // TODO replace with file utils
    std::string levelStr;
    std::filebuf fb;
    fb.open(path, std::ios::out);
    std::istream os(&fb);
    os >> levelStr;
    fb.close();

    JsonLevelData levelData;
    levelData.m_levelObject = json::parse(levelStr);

    levelData.UpdateInternalDataFromReadJson();

    Array<JsonLevelComponentData> components;

    // Create empty entities (with only children)
    for (auto& jsonEntity : levelData.m_entities)
    {
        CreateEntityFrom(jsonEntity, components);
    }

    for (auto& jsonComp : components)
    {
        CreateComponentFrom(jsonComp);
    }

    return true;
}

bool JsonLevelSerializer::SerializeEntity(const Entity* entity, JsonLevelEntityData* entityData)
{
    bool status = true;

    entityData->SetId(entity->GetId());
    entityData->SetName(entity->GetName());

    for (auto* comp : entity->GetComponents())
    {
        status = SerializeComponent(comp, entityData->AddLevelComponentData(std::string(comp->GetComponentName()))) &&
                 status;
    }

    for (auto* child : entity->GetChildren())
    {
        status = SerializeEntity(child, entityData->AddLevelChildEntityData()) && status;
    }

    return status;
}

bool JsonLevelSerializer::SerializeComponent(const Component* comp, JsonLevelComponentData* compData)
{
    auto* compRegistry = comp->GetWorld()->GetComponentRegistry();

    const auto* compTypeTraits = compRegistry->GetComponentTraits(std::string(comp->GetComponentName()));

    if (compTypeTraits == nullptr)
    {
        RED_LOG_ERROR("Failed to serialize component {}. You forgot to register it",
                      std::string(comp->GetComponentName()));
        return false;
    }

    for (auto& memberIt : compTypeTraits->members)
    {
        auto serializedMember = memberIt.second.serializationFunction(comp);

        compData->AddPairOfValue(memberIt.second.name, serializedMember);
    }

    return true;
}

void JsonLevelSerializer::CreateEntityFrom(const JsonLevelEntityData& jsonEntity,
                                           Array<JsonLevelComponentData>& entityComponents)
{
    std::string name = jsonEntity.GetName();
    int id = jsonEntity.GetId();

    auto* entity = m_level->CreateEntity(id, name);

    for (auto& compData : entityComponents)
    {
        CreateComponentFrom(entity, compData);
    }
}

void JsonLevelSerializer::CreateComponentFrom(Entity* entity, const JsonLevelComponentData& jsonComp)
{
    jsonComp.
}
*/
}  // namespace red
