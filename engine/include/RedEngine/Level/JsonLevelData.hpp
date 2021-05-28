#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Level/LevelData.hpp"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace red
{
class JsonLevelComponentData : public ILevelComponentData
{
    friend class Level;
    friend class Entity;
    friend class Component;

public:
    explicit JsonLevelComponentData(json* object);
    ~JsonLevelComponentData() = default;

    void AddPairOfValue(const std::string& name, const std::string& value) override;

private:
    json* m_componentObject;
};

class JsonLevelEntityData : public ILevelEntityData
{
    friend class Level;
    friend class Entity;

public:
    explicit JsonLevelEntityData(json* entityObject);
    ~JsonLevelEntityData() = default;

    JsonLevelComponentData* AddLevelComponentData(const std::string& componentName) override;
    JsonLevelEntityData* AddLevelChildEntityData() override;

    void SetName(const std::string& name) override;
    void SetId(const EntityId& id) override;
    void SetParentId(const EntityId& parentId) override;

private:
    Array<JsonLevelComponentData> m_components;
    Array<JsonLevelEntityData> m_children;
    json* m_entityObject;
};

class JsonLevelData : public ILevelData
{
    friend class Level;

public:
    JsonLevelData() = default;
    ~JsonLevelData() = default;

    JsonLevelEntityData* AddLevelEntityData() override;

private:
    Array<JsonLevelEntityData> m_entities;
    json m_levelObject;
};
}  // namespace red