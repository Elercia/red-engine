#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

namespace red
{
class World;
class Component;
class Entity;

using ComponentPoolType = Map<EntityId, Component*>;

class ComponentManager
{
public:
    ComponentManager(World* world);
    ~ComponentManager();

    template <typename ComponentType_t, typename... Args>
    ComponentType_t* CreateComponent(Entity* owner, Args&&... args);

    template <typename ComponentType_t>
    bool RemoveComponent(Entity* owner);

    void RemoveAllComponentsOf(Entity* owner);

    Array<Component*> GetComponents(const Entity* entity) const;

    template <class ComponentType_t>
    bool HasComponent(Entity* entity);

    template <typename ComponentType_t>
    ComponentType_t* GetComponent(Entity* entity);

    bool HasComponent(Entity* entity, const std::string& componentName);
    Component* GetComponent(Entity* entity, const std::string& componentName);
    bool RemoveComponent(Entity* entity, const std::string& componentName);
    Component* CreateComponentFromName(Entity* entity, const std::string& componentName);

private:
    ComponentPoolType& GetComponentPool(std::size_t componentTypeId);

    void AddComponent(Entity* entity, Component* component);

private:
    World* m_world;
    Map<std::size_t, ComponentPoolType> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
