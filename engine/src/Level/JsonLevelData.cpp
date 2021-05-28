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

    componentArray[componentName] = json::object();

    m_components.emplace_back(&componentArray[componentName]);

    return &(m_components.back());
}

JsonLevelEntityData* JsonLevelEntityData::AddLevelChildEntityData()
{
    json& childrenArray = (*m_entityObject)["children"];

    childrenArray.push_back({});

    json& childNode = childrenArray.back();

    m_children.emplace_back(&childNode);

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

void JsonLevelEntityData::SetParentId(const EntityId& parentId)
{
    (*m_entityObject)["parentId"] = parentId;
}

red::JsonLevelEntityData* JsonLevelData::AddLevelEntityData()
{
    json& entityObject = m_levelObject.emplace_back();
    return &m_entities.emplace_back(&entityObject);
}

}  // namespace red
