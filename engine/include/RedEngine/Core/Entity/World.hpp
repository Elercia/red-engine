#pragma once

#include <RedEngine/RedEngineBase.hpp>

#include <RedEngine/Utils/Uncopyable.hpp>

#include "../EngineConfig.hpp"

#include <Box2D/Dynamics/b2World.h>

#include <memory>
#include <vector>
#include <string>

namespace red
{
class Entity;
class ComponentManager;
class Component;
class System;
class Level;

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
    Entity* CreateEntity(const std::string& name, Entity* root = nullptr);
    Entity* CreateSingletonEntity();

    template <class T, class... Args>
    T* AddSystem(Args... args);
    template <class T>
    void RemoveSystem();

    const std::vector<System*>& GetSystems();
    const std::vector<Entity*>& GetEntities();
    Entity* GetSingletonEntity();
    ComponentManager* GetComponentManager();

    void Init();
    void Update();

    void Clean();

    b2World* GetPhysicsWorld();


private:

    Entity* m_singletonEntity;
    std::vector<Entity*> m_entities;
    std::vector<System*> m_systems;
    ComponentManager* m_componentManager;

    EntityId_t m_nextEntityId;

    b2World m_physicsWorld;  // TODO IPhysicsWorld
};

}  // namespace red

#include "inl/World.inl"
