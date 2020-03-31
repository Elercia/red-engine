#include "../../../Debug/Debug.hpp"

namespace red
{
template <typename ComponentType_t, typename... Args>
ComponentType_t* ComponentManager::CreateComponent(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value,
                  "ComponentType is not a Component type");

    auto sharedComponent = new ComponentType_t(owner, std::forward<Args>(args)...);

    auto foundComponentPoolIt = m_components.find(ComponentType_t::ComponentName);

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

template <class ComponentType_t>
bool ComponentManager::HasComponent(Entity* entity)
{
    return false;
}

template <typename ComponentType_t>
ComponentType_t* ComponentManager::GetComponent(Entity* entity)
{
    return nullptr;
}
}  // namespace red
