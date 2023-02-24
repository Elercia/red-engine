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

    template <typename ComponentTypeT, typename... Args>
    ComponentTypeT* CreateComponent(Entity* owner, Args&&... args);

    template <typename ComponentTypeT>
    bool RemoveComponent(Entity* owner);

    void RemoveAllComponentsOf(Entity* owner);

    Array<Component*> GetComponents(const Entity* entity) const;

    template <typename ComponentTypeT>
    ComponentTypeT* GetComponent(Entity* entity);

    Component* GetComponent(Entity* entity, const TypeTraits& componentTraits);
    bool RemoveComponent(Entity* entity, const TypeTraits& componentTraits);
    Component* CreateComponentFromName(Entity* entity, const TypeTraits& componentTraits);

private:
    ComponentPoolType& GetComponentPool(const TypeTraits& componentTraits);

    void AddComponent(Entity* entity, Component* component);

private:
    World* m_world;
    Map<TypeTraitsId, ComponentPoolType> m_components;
};
}  // namespace red

#include "inl/ComponentManager.inl"
