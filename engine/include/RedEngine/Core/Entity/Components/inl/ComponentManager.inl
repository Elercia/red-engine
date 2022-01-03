#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
template <typename ComponentType_t, typename... Args>
ComponentType_t* ComponentManager::CreateComponent(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value, "ComponentType is not a Component type");

    auto* comp = GetComponent<ComponentType_t>(owner);
    if (comp)
    {
        // Fixme should reduce includes by removing Entity dereference from here
        /*RED_LOG_WARNING("Entity {} already have a component of type {} (strict type is {})", owner->GetId(),
                        TypeInfo<ComponentType_t>().name, comp->GetComponentName());*/
        return comp;
    }

    auto* createdComponent = new ComponentType_t(owner, std::forward<Args>(args)...);

    AddComponent(owner, createdComponent);

    return createdComponent;
}

template <typename ComponentType_t>
bool ComponentManager::RemoveComponent(Entity* owner)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value, "ComponentType is not a Component type");

    return RemoveComponent(owner, std::string(TypeInfo<ComponentType_t>().name));
}

template <class ComponentType_t>
bool ComponentManager::HasComponent(Entity* entity)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value, "ComponentType is not a Component type");

    return HasComponent(entity, std::string(TypeInfo<ComponentType_t>().name));
}

template <typename ComponentType_t>
ComponentType_t* ComponentManager::GetComponent(Entity* entity)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value, "ComponentType is not a Component type");

    auto* componentPtr = GetComponent(entity, std::string(TypeInfo<ComponentType_t>().name));
    return reinterpret_cast<ComponentType_t*>(componentPtr);
}
}  // namespace red
