#pragma once

#include "RedEngine/Utils/TypesInfo.hpp"
#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/CommonEntityTypes.hpp"

#include <map>

namespace red
{
class World;
class Component;
class Entity;

using ComponentPoolType = std::map<EntityId, Component*>;

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

    Component* CreateComponent(Entity* owner, const std::string& name);
    bool HasComponent(Entity* entity, const std::string& name);
    Component* GetComponent(Entity* entity, const std::string& name);

private:
    ComponentPoolType& GetComponentPool(std::size_t componentTypeId);
    void StoreComponent(Entity* owner, Component* component, std::size_t name);

    void RemoveComponent(Entity* owner, ComponentPoolType& pool);

    bool HasComponent(Entity* entity, std::size_t name);

    Component* GetComponent(Entity* entity, std::size_t name);

private:
    World* m_world;
    std::map<std::size_t, ComponentPoolType> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
