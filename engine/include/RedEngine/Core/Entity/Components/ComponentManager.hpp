#pragma once

#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Core/Container/Array.hpp"

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace red
{
class World;
class Component;
class Entity;

using EntityId = uint32;
using ComponentPool_t = Component**;

constexpr int ComponentPoolSize = 2048;

class ComponentManager
{
public:
    ComponentManager(World* world);
    ~ComponentManager();

    template <typename ComponentType_t, typename... Args>
    ComponentType_t* CreateComponent(Entity* owner, Args&&... args);
    
    template <typename ComponentType_t>
    void RemoveComponent(Entity* owner);

    Array<Component*> GetComponents(const Entity* entity) const;

    template <class ComponentType_t>
    bool HasComponent(Entity* entity);

    template <typename ComponentType_t>
    ComponentType_t* GetComponent(Entity* entity);

    void MoveComponents(EntityId from, EntityId to);

    Component* CreateComponent(Entity* owner, const std::string& name);
    bool HasComponent(Entity* entity, const std::string& name);
    Component* GetComponent(Entity* entity, const std::string& name);

    void UnloadTransientComponents();

private:
    ComponentPool_t& GetComponentPool(std::size_t componentName);
    void StoreComponent(Entity* owner, Component* component, std::size_t name);

    void RemoveComponent(Entity* owner, ComponentPool_t& pool);

    bool HasComponent(Entity* entity, std::size_t name);

    Component* GetComponent(Entity* entity, std::size_t name);

private:
    World* m_world;
    std::map<std::size_t, ComponentPool_t> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
