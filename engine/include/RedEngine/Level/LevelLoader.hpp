#pragma once

#include "LevelData.hpp"

#include "RedEngine/Filesystem/Path.hpp"

namespace red
{
class Entity;
class World;
class Level;

class LevelLoader
{
public:
    LevelLoader(World* world);
    ~LevelLoader();

    Level* LoadLevel(const Path& path);

private:
    virtual LevelData ReadLevelData(const Path& path) = 0;
    Level* ParseLevelData(const LevelData& levelData);

    void CreateEntity(Level* level, const EntityData& entityData, Entity* parent = nullptr);
    void CreateComponent(const ComponentData& componentData, Entity* owner);

protected:
    World* m_world;
};
}  // namespace red
