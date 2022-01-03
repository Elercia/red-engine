#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"

#include "RedEngine/Core/CoreModule.hpp"

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

bool ComponentManager::HasComponent(Entity* entity, const std::string& componentName)
{
    return GetComponent(entity, componentName) != nullptr;
}

Component* ComponentManager::GetComponent(Entity* entity, const std::string& componentName)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(componentName);

    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered", componentName);
        return nullptr;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);
    auto compIt = componentPool.find(entity->GetId());

    if (compIt == componentPool.end())
    {
        for (const auto* childCompTraits : traits->childComponentTraits)
        {
            auto* component = GetComponent(entity, std::string(childCompTraits->componentName));

            if (component != nullptr)
            {
                return component;
            }
        }

        return nullptr;
    }

    return compIt->second;
}

void ComponentManager::AddComponent(Entity* entity, Component* component)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(std::string(component->GetComponentName()));

    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered",
                      component->GetComponentName());
        return;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);

    componentPool[entity->GetId()] = component;
}

bool ComponentManager::RemoveComponent(Entity* entity, const std::string& componentName)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(componentName);

    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered", componentName);
        return false;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);

    auto it = componentPool.find(entity->GetId());

    if (it != componentPool.end())
    {
        delete it->second;
        componentPool.erase(it);
        return true;
    }

    for (const auto* childCompTraits : traits->childComponentTraits)
    {
        auto removed = RemoveComponent(entity, std::string(childCompTraits->componentName));

        if (removed)
        {
            return true;
        }
    }

    return false;
}

Component* ComponentManager::CreateComponentFromName(Entity* entity, const std::string& componentName)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(componentName);
    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component with name {} because it is not registered", componentName);
        return nullptr;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeId);
    auto* comp = traits->creator(entity);

    componentPool[entity->GetId()] = comp;

    return comp;
}
}  // namespace red
