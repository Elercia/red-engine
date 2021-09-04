#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
ComponentManager::ComponentManager(World* world) : m_world(world)
{
}

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

Component* ComponentManager::CreateComponent(Entity* owner, const std::string& name)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(name);

    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered", name);
        return nullptr;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);
    Component* comp = traits->creator(owner);

    componentPool[owner->GetId()] = comp;

    return comp;
}

bool ComponentManager::HasComponent(Entity* entity, const std::string& name)
{
    return GetComponent(entity, name) != nullptr;
}

Component* ComponentManager::GetComponent(Entity* entity, const std::string& name)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(name);

    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered", name);
        return false;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);

    return componentPool[entity->GetId()];
}

Array<Component*> ComponentManager::GetComponents(const Entity* entity) const
{
    Array<Component*> entityComponents;

    for (auto& compPoolPair : m_components)
    {
        auto** compPool = compPoolPair.second;

        auto* comp = compPool[entity->GetId()];

        if (comp != nullptr)
        {
            entityComponents.push_back(comp);
        }
    }

    return entityComponents;
}

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
    auto ptr = pool[owner->GetId()];

    delete ptr;

    pool[owner->GetId()] = nullptr;
}

bool ComponentManager::HasComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()] != nullptr;
}

Component* ComponentManager::GetComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()];
}

void ComponentManager::MoveComponents(EntityId from, EntityId to)
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
