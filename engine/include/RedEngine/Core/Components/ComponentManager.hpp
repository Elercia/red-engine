#pragma once

#include "../EngineConfig.hpp"

#include "RedEngine/RedEngineBase.hpp"

#include <map>
#include <memory>
#include <set>
#include <vector>

namespace red
{
class Component;
class Entity;

using ComponentPool_t = Component**;

class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager();

    template <typename ComponentType_t, typename... Args>
    ComponentType_t* CreateComponent(Entity* owner, Args&&... args);

    template <typename ComponentType_t>
    void RemoveComponent(Entity* owner);

    std::set<Component*> GetComponents(Entity* entity);

    template <class ComponentType_t>
    bool HasComponent(Entity* entity);

    template <typename ComponentType_t>
    ComponentType_t* GetComponent(Entity* entity);

    void MoveComponents(EntityId_t from, EntityId_t to);

    void UnloadTransientComponents();

private:
    ComponentPool_t& GetComponentPool(std::size_t componentName);
    void StoreComponent(Entity* owner, Component* component, std::size_t name);

    void RemoveComponent(Entity* owner, ComponentPool_t& pool);

    bool HasComponent(Entity* entity, std::size_t name);

    Component* GetComponent(Entity* entity, std::size_t name);

    std::map<std::size_t, ComponentPool_t> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
