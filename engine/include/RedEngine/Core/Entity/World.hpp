#pragma once

#include "RedEngine/Core/Entity/Components/ComponentRegistry.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>
#include <vector>

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

    Entity* CreateRootEntity(Level* level);
    Entity* CreateEntity(Entity* root = nullptr);
    Entity* CreateEntity(EntityId id, const std::string& name, Entity* root = nullptr);
    Entity* CreateEntity(const std::string& name, Entity* root = nullptr);

    Entity* CreateSingletonEntity();

    Entity* FindEntity(EntityId id);

    template <class T, class... Args>
    T* AddSystem(Args... args);
    template <class T>
    void RemoveSystem();
    template <class T>
    T* GetSystem();

    template <typename T>
    void LoadLevel();

    void LoadLevel(const Path& levelPath);

    void ChangeLevel(Level* newLevel);

    template <class T>
    T* GetSingletonComponent();

    const std::vector<System*>& GetSystems();
    const std::vector<Entity*>& GetEntities();
    Entity* GetSingletonEntity();
    ComponentManager* GetComponentManager();
    ComponentRegistry* GetComponentRegistry();

    void Init();
    void Finalize();

    bool Update();

    void Clean();

    PhysicsWorld* GetPhysicsWorld();

    template <typename T>
    bool RegisterComponentType();

    Level* GetCurrentLevel();

private:
    Entity* m_singletonEntity;

    std::vector<Entity*> m_entities;
    std::vector<System*> m_systems;
    ComponentManager* m_componentManager;
    ComponentRegistry* m_componentRegistry;
    PhysicsWorld m_physicsWorld;

    EntityId m_nextEntityId;

    Level* m_currentLevel;
    LevelLoader* m_levelLoader;
};

}  // namespace red

#include "inl/World.inl"
