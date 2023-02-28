#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"

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

ComponentPoolType& ComponentManager::GetComponentPool(const TypeTraits& componentTraits)
{
    auto poolIt = m_components.find(componentTraits.typeId);
    if (poolIt != m_components.end())
    {
        return poolIt->second;
    }

    auto [it, inserted] = m_components.insert({componentTraits.typeId, {}});
    RedAssert(inserted, "Counldn't insert a new component pool")

        return it->second;
}

Component* ComponentManager::GetComponent(Entity* entity, const TypeTraits& componentTraits)
{
    auto& componentPool = GetComponentPool(componentTraits);
    auto compIt = componentPool.find(entity->GetId());

    if (compIt == componentPool.end())
    {
        return nullptr;
    }

    return compIt->second;
}

void ComponentManager::AddComponent(Entity* entity, Component* component)
{
    auto& componentPool = GetComponentPool(component->GetTypeTraits());

    componentPool[entity->GetId()] = component;
}

bool ComponentManager::RemoveComponent(Entity* entity, const TypeTraits& componentTraits)
{
    auto& componentPool = GetComponentPool(componentTraits);

    auto it = componentPool.find(entity->GetId());

    if (it != componentPool.end())
    {
        delete it->second;
        componentPool.erase(it);
        return true;
    }

    return false;
}

void ComponentManager::RemoveAllComponentsOf(Entity* owner)
{
    for (auto& itCompType : m_components)
    {
        auto& comonentPool = itCompType.second;
        auto it = comonentPool.find(owner->GetId());

        if (it != comonentPool.end())
        {
            RED_SAFE_DELETE(it->second);
            comonentPool.erase(it);
        }
    }
}

Component* ComponentManager::CreateComponentFromName(Entity* entity, const TypeTraits& componentTraits)
{
    auto* registry = m_world->GetComponentRegistry();
    auto* traits = registry->GetComponentTraits(componentTraits.typeId);
    if (traits == nullptr)
    {
        RED_LOG_ERROR("Failed to create component from name with name {} because it is not registered",
                      componentTraits.name);
        return nullptr;
    }

    auto& componentPool = GetComponentPool(traits->componentTypeTraits);
    auto* comp = traits->creator(entity);

    componentPool[entity->GetId()] = comp;

    return comp;
}
}  // namespace red
