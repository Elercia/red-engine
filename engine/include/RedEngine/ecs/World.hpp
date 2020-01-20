#pragma once

#include "../EngineConfig.hpp"
#include "../Utils.hpp"
#include "System.hpp"

#include <memory>
#include <vector>

namespace red
{
class Entity;
class ComponentManager;
class Component;

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

    std::shared_ptr<Entity> CreateEntity();

    template <class T>
    std::shared_ptr<T> AddSystem(...);

    std::vector<std::shared_ptr<System>>& GetSystems();
    ComponentManager* GetComponentManager();

    void Update(float deltaTime);

private:
    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<System>> m_systems;
    ComponentManager* m_componentManager;

    EntityId_t m_nextEntityId;
};

} // namespace red

#include "inl/World.inl"
