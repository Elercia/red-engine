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
        auto& pool = componentPoolPair.second;

        for (auto& compIt : pool)
        {
            delete compIt.second;
        }
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
        auto& compPool = compPoolPair.second;

        auto compIt = compPool.find(entity->GetId());

        if (compIt != compPool.end())
        {
            entityComponents.push_back(compIt->second);
        }
    }

    return entityComponents;
}

void ComponentManager::StoreComponent(Entity* owner, Component* component, std::size_t name)
{
    auto& componentPool = GetComponentPool(name);
    componentPool[owner->GetId()] = component;
}

ComponentPoolType& ComponentManager::GetComponentPool(std::size_t componentTypeId)
{
    auto poolIt = m_components.find(componentTypeId);
    if (poolIt != m_components.end())
    {
        return poolIt->second;
    }

    auto [it, inserted] = m_components.insert({componentTypeId, {}});
    RED_ASSERT(inserted, "Counldn't insert a new component pool")

    return it->second;
}

void ComponentManager::RemoveComponent(Entity* owner, ComponentPoolType& pool)
{
    auto ptr = pool[owner->GetId()];

    delete ptr;

    pool.erase(owner->GetId());
}

bool ComponentManager::HasComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()] != nullptr;
}

Component* ComponentManager::GetComponent(Entity* entity, std::size_t name)
{
    return GetComponentPool(name)[entity->GetId()];
}
}  // namespace red
