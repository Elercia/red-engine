#pragma once
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>

namespace red
{
class Level;
class World;
class Entity;

class LevelChunk : Uncopyable
{
    friend Level;
    friend World;

public:
    explicit LevelChunk(Level* owner);
    explicit LevelChunk(World* owner);
    ~LevelChunk();

    Array<Entity*>& GetEntities();
    const Array<Entity*>& GetEntities() const;

    Entity* GetRootEntity();
    const Entity* GetRootEntity() const;

    void Init();
    void Finalize();
    void Clean();

private:
    // Create entities need to come from World (world chunk) or level (levelChunk)
    Entity* CreateEntity();
    Entity* CreateEntity(EntityId entityId);
    Entity* CreateEntity(EntityId entityId, Entity* parent);
    Entity* CreateEntity(EntityId entityId, const std::string& name);
    Entity* CreateEntity(EntityId entityId, const std::string& name, Entity* parent);
    Entity* CreateEntity(const std::string& name);
    Entity* CreateEntity(const std::string& name, Entity* parent);

private:
    Array<Entity*> m_ownedEntities;
    Entity* m_rootEntity;
    Level* m_level;
    World* m_world;
};
}  // namespace red
