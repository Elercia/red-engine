#pragma once

#include "RedEngine/Level/LevelLoader.hpp"

#include <nlohmann/json.hpp>

namespace red
{
class Level;
using json = Json;

class JsonLevelLoader : public LevelLoader
{
public:
    JsonLevelLoader(World* world);
    virtual ~JsonLevelLoader();

    virtual LevelData ReadLevelData(const Path& path) override;

private:
    ComponentData ParseComponent(const String& componentName, json componentJson);
    EntityData ParseEntity(json jsonEntityData);
};
}  // namespace red
