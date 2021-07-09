#include "RedEngine/Level/JsonLevelData.hpp"

namespace red
{
///--- Components
///---------------------------------------------

JsonLevelComponentData::JsonLevelComponentData(json* object) : m_componentObject(object)
{
}

void JsonLevelComponentData::AddPairOfValue(const std::string& name, const std::string& value)
{
    (*m_componentObject)[name] = value;
}

///--- Entity
///---------------------------------------------

JsonLevelEntityData::JsonLevelEntityData(json* entityObject) : m_entityObject(entityObject)
{
}

JsonLevelComponentData* JsonLevelEntityData::AddLevelComponentData(const std::string& componentName)
{
    json& componentArray = (*m_entityObject)["components"];

    auto& obj = componentArray.emplace_back();

    return AddLevelComponentData(componentName, obj);
}

red::JsonLevelComponentData* JsonLevelEntityData::AddLevelComponentData(const std::string& componentName, json& jsonObj)
{
    jsonObj["componentName"] = componentName;

    m_components.emplace_back(&jsonObj);

    return &(m_components.back());
}

JsonLevelEntityData* JsonLevelEntityData::AddLevelChildEntityData()
{
    json& childrenArray = (*m_entityObject)["children"];

    childrenArray.push_back({});

    json& childNode = childrenArray.back();

    return AddLevelChildEntityData(childNode);
}

JsonLevelEntityData* JsonLevelEntityData::AddLevelChildEntityData(json& entityJson)
{
    m_children.emplace_back(&entityJson);

    return &(m_children.back());
}

void JsonLevelEntityData::SetName(const std::string& name)
{
    (*m_entityObject)["name"] = name;
}

void JsonLevelEntityData::SetId(const EntityId& id)
{
    (*m_entityObject)["id"] = id;
}

std::string JsonLevelEntityData::GetName() const
{
    return (*m_entityObject)["name"];
}

int JsonLevelEntityData::GetId() const
{
    return (*m_entityObject)["id"];
}

///--- Level
///---------------------------------------------

red::JsonLevelEntityData* JsonLevelData::AddLevelEntityData()
{
    json& entitiesJsonArray = m_levelObject["entities"];

    entitiesJsonArray.push_back({});

    json& entityNode = entitiesJsonArray.back();

    return AddLevelEntityData(entityNode);
}

red::JsonLevelEntityData* JsonLevelData::AddLevelEntityData(json& entityJson)
{
    return &m_entities.emplace_back(&entityJson);
}

void JsonLevelData::UpdateInternalDataFromReadJson()
{
    auto& jsonEntityArray = m_levelObject["entities"];

    for (auto& jsonEntity : jsonEntityArray)
    {
        UpdateInternalDataForEntity(jsonEntity, nullptr);
    }
}

void JsonLevelData::UpdateInternalDataForEntity(json& jsonEntity, JsonLevelEntityData* parentData)
{
    auto* entity =
        parentData != nullptr ? parentData->AddLevelChildEntityData(jsonEntity) : AddLevelEntityData(jsonEntity);

    auto& jsonChildrenEntityArray = jsonEntity["children"];
    auto& jsonComponentObjects = jsonEntity["components"];

    for (auto& jsonChildEntity : jsonChildrenEntityArray)
    {
        UpdateInternalDataForEntity(jsonChildEntity, entity);
    }

    for (auto it = jsonComponentObjects.begin(); it != jsonComponentObjects.end(); ++it)
    {
        entity->AddLevelComponentData(it.key(), it.value());
    }
}

}  // namespace red
