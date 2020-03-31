#pragma once

#include <memory>
#include <vector>

#include "../EngineConfig.hpp"

namespace red
{
class Entity;
class ComponentManager;
class Component;
class System;

class World
{
    friend Entity;
    friend Component;

public:
    World();
    ~World();

    World(World&) = delete;
    World(World&&) = delete;

    World& operator=(const World& world) = delete;
    World& operator=(World&& world) = delete;

    Entity* CreateEntity();
    void DestroyEntity(Entity* entity);

    template <class T, class... Args>
    T* AddSystem(Args... args);

    const std::vector<System*>& GetSystems();
    const std::vector<Entity*>& GetEntities();
    ComponentManager* GetComponentManager();

    void Update(float deltaTime);

private:
    std::vector<Entity*> m_entities;
    std::vector<System*> m_systems;
    ComponentManager* m_componentManager;

    EntityId_t m_nextEntityId;
};

}  // namespace red

#include "inl/World.inl"
