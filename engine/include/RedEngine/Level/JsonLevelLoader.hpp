#pragma once

#include "RedEngine/Level/LevelLoader.hpp"

#include <nlohmann/json.hpp>

namespace red
{
class Level;
using json = nlohmann::json;

class JsonLevelLoader : public LevelLoader
{
public:
    JsonLevelLoader(World* world);
    ~JsonLevelLoader();

    virtual LevelData ReadLevelData(const Path& path) override;

private:
    ComponentData ParseComponent(const std::string& componentName, json componentJson);
    EntityData ParseEntity(json jsonEntityData);
};
}  // namespace red
