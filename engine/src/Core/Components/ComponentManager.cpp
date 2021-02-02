#include "RedEngine/Core/Components/ComponentManager.hpp"

#include "RedEngine/Core/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"

namespace red
{
ComponentManager::ComponentManager() : m_components() {}

ComponentManager::~ComponentManager()
{
    for (auto componentPoolPair : m_components)
    {
        auto* pool = componentPoolPair.second;
        for (int i = 0; i < ComponentPoolSize; ++i)
        {
            delete pool[i];
        }

        free(pool);
    }
}

std::set<Component*> ComponentManager::GetComponents(Entity* /*entity*/) { return {}; }  // TODO

void ComponentManager::StoreComponent(Entity* owner, Component* component, std::size_t name)
{
    auto& componentPool = GetComponentPool(name);
    componentPool[owner->GetId()] = component;
}

ComponentPool_t& ComponentManager::GetComponentPool(std::size_t componentName)
{
    auto poolIt = m_components.find(componentName);
    if (poolIt != m_components.end())
    {
        return poolIt->second;
    }

    auto* pool = (ComponentPool_t) calloc(sizeof(Component*), ComponentPoolSize);
    return m_components.insert({componentName, pool}).first->second;
}

void ComponentManager::RemoveComponent(Entity* owner, ComponentPool_t& pool)
{
    auto& ptr = pool[owner->GetId()];

    delete ptr;

    ptr = nullptr;
}

bool ComponentManager::HasComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()] != nullptr;
}

Component* ComponentManager::GetComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()];
}

void ComponentManager::MoveComponents(EntityId_t from, EntityId_t to)
{
    for (auto componentPoolPair : m_components)
    {
        auto* pool = componentPoolPair.second;

        pool[to] = pool[from];
        pool[from] = nullptr;
    }
}

void ComponentManager::UnloadTransientComponents()
{
    for (auto componentPoolPair : m_components)
    {
        auto* pool = componentPoolPair.second;

        for (int i = 0; i < ComponentPoolSize; ++i)
        {
            delete pool[i];
        }
    }
}

}  // namespace red
