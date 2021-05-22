#include "RedEngine/Level/JsonLevelData.hpp"

namespace red
{
///--- Components
///---------------------------------------------

JsonLevelComponentData::JsonLevelComponentData(json* object) : m_componentObject(object)
{
}

void JsonLevelComponentData::WriteVector2(const std::string& name, Vector2 vec2)
{
    json vec2Object;

    vec2Object["x"] = vec2.x;
    vec2Object["y"] = vec2.y;

    (*m_componentObject)[name] = vec2Object;
}

Vector2 JsonLevelComponentData::ReadVector2(const std::string& name) const
{
    Vector2 vec;

    auto vec2Object = m_componentObject->find(name);

    RED_ASSERT_S(vec2Object != m_componentObject->end());
    RED_ASSERT_S((*vec2Object)["x"].is_number_float() && (*vec2Object)["y"].is_number_float());

    vec.x = (*vec2Object)["x"].get<float>();
    vec.y = (*vec2Object)["y"].get<float>();

    return vec;
}

void JsonLevelComponentData::SetName(const std::string& name)
{
    (*m_componentObject)["name"] = name;
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
