#pragma once

#include <map>
#include <memory>
#include <set>
#include <vector>

#include "../EngineConfig.hpp"

namespace red
{
class Entity;
class Component;

using ComponentPool_t = std::vector<Component*>;

class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager() = default;

    template <typename ComponentType_t, typename... Args>
    ComponentType_t* CreateComponent(Entity* owner, Args&&... args);

    template <typename ComponentType>
    void RemoveComponent(Entity* owner);

    std::set<Component*> GetComponents(Entity* entity);

    template <class ComponentType_t>
    bool HasComponent(Entity* entity);

    template <typename ComponentType_t>
    ComponentType_t* GetComponent(Entity* entity);

private:
    std::map<ComponentName_t, ComponentPool_t> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
