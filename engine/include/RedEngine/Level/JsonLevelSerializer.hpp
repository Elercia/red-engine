#pragma once

#include "RedEngine/Level/JsonLevelData.hpp"
#include "RedEngine/Level/LevelSerializer.hpp"

namespace red
{
class Level;
class Entity;

class JsonLevelSerializer : public ILevelSerializer
{
public:
    explicit JsonLevelSerializer(Level* level);

    bool SerializeToFile(const std::string& path) override;
    bool DeserializeFromFile(const std::string& path) override;

    bool SerializeEntity(const Entity* entity, JsonLevelEntityData* entityData);
    bool SerializeComponent(const Component* comp, JsonLevelComponentData* compData);

private:
    void CreateEntityFrom(const JsonLevelEntityData& jsonEntity, Array<JsonLevelComponentData>& entityComponents);
    void CreateComponentFrom(const JsonLevelComponentData& jsonComp);
};
}  // namespace red