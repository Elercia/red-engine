#pragma once

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Physics/PhysicsWorld.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <memory>
#include <string>
#include <vector>

namespace red
{
class ComponentManager;
class Component;
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
    template <class T>
    T* GetSystem();

    template <typename T>
    void LoadLevel();

    void ChangeLevel(Level* newLevel);

    template <class T>
    T* GetSingletonComponent();

    const std::vector<System*>& GetSystems();
    const std::vector<Entity*>& GetEntities();
    Entity* GetSingletonEntity();
    ComponentManager* GetComponentManager();

    void Init();
    void Finalize();

    bool Update();

    void Clean();

    PhysicsWorld* GetPhysicsWorld();

    Entity* GetCurrentRootEntity();

private:
    Entity* m_singletonEntity;
    Entity* m_currentRootEntity;

    std::vector<Entity*> m_entities;
    std::vector<System*> m_systems;
    ComponentManager* m_componentManager;
    PhysicsWorld m_physicsWorld;

    EntityId m_nextEntityId;

    Level* m_currentLevel;
};

}  // namespace red

#include "inl/World.inl"
