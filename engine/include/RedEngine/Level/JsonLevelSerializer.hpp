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
    explicit JsonLevelSerializer(const Level* level);

    virtual std::string SerializeData(const LevelData& levelData) override;

private:
    json SerializeEntity(const EntityData& entityData);
    json SerializeComponent(const ComponentData& componentData);
};
}  // namespace red