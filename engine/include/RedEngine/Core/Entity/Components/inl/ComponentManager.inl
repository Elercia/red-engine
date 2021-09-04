#include "RedEngine/Core/Debug/DebugMacros.hpp"

namespace red
{
template <typename ComponentType_t, typename... Args>
ComponentType_t* ComponentManager::CreateComponent(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<Component, ComponentType_t>::value, "ComponentType is not a Component type");

    auto component = new ComponentType_t(owner, std::forward<Args>(args)...);

    StoreComponent(owner, component, TypeInfo<ComponentType_t>().typeId);

    return component;
}

template <typename ComponentType_t>
void ComponentManager::RemoveComponent(Entity* owner)
{
    auto* pool = GetComponentPool(TypeInfo<ComponentType_t>().typeId);

    RemoveComponent(owner, pool);
}

template <class ComponentType_t>
bool ComponentManager::HasComponent(Entity* entity)
{
    return HasComponent(entity, TypeInfo<ComponentType_t>().typeId);
}

template <typename ComponentType_t>
ComponentType_t* ComponentManager::GetComponent(Entity* entity)
{
    auto* componentPtr = GetComponent(entity, TypeInfo<ComponentType_t>().typeId);
    return reinterpret_cast<ComponentType_t*>(componentPtr);
}
}  // namespace red