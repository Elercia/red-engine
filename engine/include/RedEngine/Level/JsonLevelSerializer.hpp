#pragma once

#include "RedEngine/Level/LevelSerializer.hpp"

#include <nlohmann/json.hpp>

namespace red
{
class Level;
class Entity;

class JsonLevelSerializer : public ILevelSerializer
{
    using json = nlohmann::json;

public:
    static constexpr char* LEVEL_ENTITIES = "entities";

    static constexpr char* ENTITY_CHILDREN = "children";
    static constexpr char* ENTITY_COMPONENTS = "components";
    static constexpr char* ENTITY_NAME = "name";
    static constexpr char* ENTITY_ID = "id";

public:
    explicit JsonLevelSerializer(const Level* level);

    virtual std::string SerializeData(const LevelData& levelData) override;

private:
    json SerializeEntity(const EntityData& entityData);
    json SerializeComponent(const ComponentData& componentData);
};
}  // namespace red