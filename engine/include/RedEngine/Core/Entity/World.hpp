#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Memory/PoolAllocator.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>

namespace red
{
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
    void OnRemoveEntity(Entity* entity);

    Entity* FindEntity(EntityId id);
    const Array<Entity*>& GetEntities() const;
    Array<Entity*>& GetEntities();

    Entity* CreateWorldEntity(const std::string& name);
    Entity* CreateEntity(Entity* parent);
    Entity* CreateEntity(Entity* parent, EntityId id);

    template <class T, class... Args>
    T* AddSystem(Args&&... args);
    template <class T>
    bool RemoveSystem();
    template <class T>
    T* GetSystem();

    template <typename T>
    void LoadLevel();

    void LoadLevel(const Path& levelPath);

    void ChangeLevel(Level* newLevel);

    const Array<BaseSystem*>& GetSystems() const;

    ComponentManager* GetComponentManager();
    ComponentRegistry* GetComponentRegistry();

    void Init();
    void Finalize();

    void InitSystems();

    bool Update();

    void Clean();

    PhysicsWorld* GetPhysicsWorld();

    template <typename T>
    bool RegisterComponentType();

    template <typename T>
    T* GetWorldComponent();

    Level* GetCurrentLevel();

    EntityId GetNewEntityId();

private:
    VirtualPoolAllocator m_entityAllocator;
    Array<Entity*> m_entities;

    // Collection of system working on the world
    Array<BaseSystem*> m_systems;
    Array<BaseSystem*> m_addedSystems;

    ComponentManager* m_componentManager;
    ComponentRegistry* m_componentRegistry;

    PhysicsWorld m_physicsWorld;

    Level* m_currentLevel;
    LevelLoader* m_levelLoader;
};

}  // namespace red

#include "inl/World.inl"
