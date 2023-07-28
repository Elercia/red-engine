#pragma once

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Level/LevelData.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
class Level;

class ILevelSerializer
{
public:
    explicit ILevelSerializer(const Level* level);

    bool Serialize(const Path& path);
    bool WriteToFile(const Path& path, const String& str);

    virtual String SerializeData(const LevelData& levelData) = 0;

private:
    LevelData GenerateLevelData(bool& success);
    ComponentData SerializeComponent(bool& success, const Component* component);
    EntityData SerializeEntity(bool& success, const Entity* entity);

private:
    const Level* m_level;
};
}  // namespace red