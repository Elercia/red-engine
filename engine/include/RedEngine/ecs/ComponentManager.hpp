#pragma once

#include "../EngineConfig.hpp"

#include <map>
#include <memory>
#include <vector>

namespace red
{
class Entity;
class Component;

using ComponentPool_t = std::vector<std::shared_ptr<Component>>;

class ComponentManager
{
public:
    ComponentManager();
    ~ComponentManager() = default;

    template <typename ComponentType_t, typename... Args>
    std::shared_ptr<ComponentType_t> CreateComponent(Entity* owner, Args&&... args);

    template <typename ComponentType>
    void RemoveComponent(Entity* owner);

private:
    std::map<ComponentName_t, ComponentPool_t> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
