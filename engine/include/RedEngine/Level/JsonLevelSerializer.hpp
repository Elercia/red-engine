#pragma once

#include "RedEngine/Level/LevelSerializer.hpp"

#include <nlohmann/json.hpp>

namespace red
{
class Level;
class Entity;

class JsonLevelSerializer : public ILevelSerializer
{
    using json = Json;

public:
    explicit JsonLevelSerializer(const Level* level);

    virtual String SerializeData(const LevelData& levelData) override;

private:
    json SerializeEntity(const EntityData& entityData);
    json SerializeComponent(const ComponentData& componentData);
};
}  // namespace red