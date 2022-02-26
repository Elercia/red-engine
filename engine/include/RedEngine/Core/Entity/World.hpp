#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>

namespace red
{
class LevelChunk;
class ComponentManager;
class Component;
class Level;
class LevelLoader;

class World : Uncopyable
{
    friend Entity;
    friend Component;

public:
    World();
    ~World();

    World(World&&) = delete;
    World& operator=(World&& world) = delete;

    void OnAddEntity(Entity* entity);
    void OnAddEntities(Array<Entity*>& entities);
    void OnRemoveEntity(Entity* entity);
    void OnRemoveEntities(Array<Entity*>& entities);

    Entity* FindEntity(EntityId id);
    const Array<Entity*>& GetEntities() const;
    Array<Entity*>& GetEntities();

    Entity* CreateWorldEntity(const std::string& name);

    template <class T, class... Args>
    T* AddSystem(Args... args);
    template <class T>
    bool RemoveSystem();
    template <class T>
    T* GetSystem();

    template <typename T>
    void LoadLevel();

    void LoadLevel(const Path& levelPath);

    void ChangeLevel(Level* newLevel);

    const Array<System*>& GetSystems() const;

    ComponentManager* GetComponentManager();
    ComponentRegistry* GetComponentRegistry();

    void Init();
    void Finalize();

    void InitSystems();

    bool Update();

    void Clean();
    void AddGarbageEntityId(EntityId entityId);

    PhysicsWorld* GetPhysicsWorld();

    template <typename T>
    bool RegisterComponentType();

    template <typename T>
    T* GetWorldComponent();

    Level* GetCurrentLevel();

    EntityId GetNewEntityId();

private:
    // World chunk is used to store world entities such as resource loaders, window, rendering stuff
    LevelChunk* m_worldChunk;

    // aggregation of all the entities from all the level chunk loaded (not owned by the world)
    Array<Entity*> m_entities;

    // Collection of system working on the world
    Array<System*> m_systems;

    ComponentManager* m_componentManager;
    ComponentRegistry* m_componentRegistry;

    PhysicsWorld m_physicsWorld;

    Level* m_currentLevel;
    LevelLoader* m_levelLoader;

    Array<EntityId> m_entityIdGarbage; //TODO Remove when I found a good EntityId generation algo
};

}  // namespace red

#include "inl/World.inl"
