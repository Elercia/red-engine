#include "../../debug/Debug.hpp"

namespace red
{
template <typename ComponentType_t, typename... Args>
std::shared_ptr<ComponentType_t> ComponentManager::CreateComponent(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value,
                  "ComponentType is not a Component type");

    auto sharedComponent = std::make_shared<ComponentType_t>(owner);

    auto foundComponentPoolIt = m_components.find(sharedComponent->GetComponentName());

    if (foundComponentPoolIt != m_components.end())
    {
        foundComponentPoolIt->second.push_back(sharedComponent);
    }
    else
    {
        auto componentPool = ComponentPool_t();
        componentPool.push_back(sharedComponent);

        m_components.insert(std::pair<ComponentName_t, ComponentPool_t>(
            sharedComponent->GetComponentName(), componentPool));
    }

    return sharedComponent;
}

template <typename ComponentType>
void ComponentManager::RemoveComponent(Entity* owner)
{
    auto componentTypePool = m_components.find(ComponentType::ComponentName);

    if (componentTypePool == m_components.end())
    {
        RED_ABORT("No matching component type to remove");
        return;
    }

    for (auto& component : componentTypePool->second)
    {
        if (component->GetOwner() == owner)
        {
            componentTypePool->second.erase(component);
        }
    }
}
}  // namespace red
