#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"

namespace red
{
template <typename ComponentTypeT, typename... Args>
ComponentTypeT* ComponentManager::CreateComponent(Entity* owner, Args&&... args)
{
    static_assert(std::is_base_of<Component, ComponentTypeT>::value, "ComponentType is not a Component type");

    auto* comp = GetComponent<ComponentTypeT>(owner);
    if (comp)
    {
        // Fixme should reduce includes by removing Entity dereference from here
        /*RED_LOG_WARNING("Entity {} already have a component of type {} (strict type is {})", owner->GetId(),
                        TypeInfo<ComponentTypeT>().name, comp->GetComponentName());*/
        return comp;
    }

    auto* memory = red_malloc(sizeof(ComponentTypeT));

    auto* createdComponent = new (memory) ComponentTypeT(owner, std::forward<Args>(args)...);
    createdComponent->m_typeTraits = TypeInfo<ComponentTypeT>();

    AddComponent(owner, createdComponent);

    return createdComponent;
}

template <typename ComponentTypeT>
bool ComponentManager::RemoveComponent(Entity* owner)
{
    static_assert(std::is_base_of<Component, ComponentTypeT>::value, "ComponentType is not a Component type");

    constexpr auto traits = TypeInfo<ComponentTypeT>();
    return RemoveComponent(owner, traits);
}

template <typename ComponentTypeT>
ComponentTypeT* ComponentManager::GetComponent(Entity* entity)
{
    static_assert(std::is_base_of<Component, ComponentTypeT>::value, "ComponentType is not a Component type");

    constexpr auto traits = TypeInfo<ComponentTypeT>();
    auto* componentPtr = GetComponent(entity, traits);
    return reinterpret_cast<ComponentTypeT*>(componentPtr);
}
}  // namespace red
