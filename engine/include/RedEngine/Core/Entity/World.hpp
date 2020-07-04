#pragma once

#include <RedEngine/Utils/Uncopyable.hpp>

#include "../EngineConfig.hpp"

#include <memory>
#include <vector>
#include <string>

namespace red
{
class Entity;
class ComponentManager;
class Component;
class System;

class World : Uncopyable
{
    friend Entity;
    friend Component;

public:
    World();
    ~World();

    World(World&&) = delete;
    World& operator=(World&& world) = delete;

    Entity* CreateEntity();
    Entity* CreateEntity(const std::string& name);
    Entity* CreateSingletonEntity();

    void SetEntityPersistency(Entity* entity, bool persistent);

    template <class T, class... Args>
    T* AddSystem(Args... args);
    template <class T>
    void RemoveSystem();

    const std::vector<System*>& GetSystems();
    const std::vector<Entity*>& GetEntities();
    Entity& GetSingletonEntity();
    ComponentManager* GetComponentManager();

    void Init();
    void Update();

    void UnloadTransientEntities();
    void UnloadSystems();

private:
    void DestroyEntity(Entity* entity);

    Entity* m_singletonEntity;
    std::vector<Entity*> m_entities;
    std::vector<System*> m_systems;
    ComponentManager* m_componentManager;

    EntityId_t m_nextEntityId;
    EntityId_t m_nextPersistentEntityId;
};

}  // namespace red

#include "inl/World.inl"
