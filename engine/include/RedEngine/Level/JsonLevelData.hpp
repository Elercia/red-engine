#pragma once

#include "RedEngine/Core/Container/Array.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace red
{
using EntityId = uint32;

class JsonLevelComponentData
{
    friend class Level;
    friend class Entity;
    friend class Component;
    friend class JsonLevelData;
    friend class JsonLevelEntityData;
    friend class JsonLevelSerializer;

public:
    explicit JsonLevelComponentData(json* object);
    ~JsonLevelComponentData() = default;

    void AddPairOfValue(const std::string& name, const std::string& value);

private:
    json* m_componentObject;
};

class JsonLevelEntityData
{
    friend class Level;
    friend class Entity;
    friend class JsonLevelData;
    friend class JsonLevelSerializer;

public:
    explicit JsonLevelEntityData(json* entityObject);
    ~JsonLevelEntityData() = default;

    JsonLevelComponentData* AddLevelComponentData(const std::string& componentName, json& jsonObj);
    JsonLevelComponentData* AddLevelComponentData(const std::string& componentName);
    JsonLevelEntityData* AddLevelChildEntityData();
    JsonLevelEntityData* AddLevelChildEntityData(json& entityJson);

    void SetName(const std::string& name);
    void SetId(const EntityId& id);

    std::string GetName() const;
    int GetId() const;

private:
    Array<JsonLevelComponentData> m_components;
    Array<JsonLevelEntityData> m_children;
    json* m_entityObject;
};

class JsonLevelData
{
    friend class Level;
    friend class JsonLevelSerializer;

public:
    JsonLevelData() = default;
    ~JsonLevelData() = default;

    JsonLevelEntityData* AddLevelEntityData();
    JsonLevelEntityData* AddLevelEntityData(json& entityJson);

    void UpdateInternalDataFromReadJson();
    void UpdateInternalDataForEntity(json& jsonEntity, JsonLevelEntityData* parentData);

    Array<JsonLevelEntityData> m_entities;
    json m_levelObject;
};
}  // namespace red