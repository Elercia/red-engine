
#include "RedEngine/Core/Components/ComponentManager.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Entity/World.hpp"

#include <algorithm>
#include <cassert>
#include <string>

namespace red
{
template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto* componentManager = m_world->GetComponentManager();

    if (componentManager->HasComponent<T>(this))
    {
        return componentManager->GetComponent<T>(
            this);  // TODO Not the best solution. This return does not respect the args sent
    }

    auto componentPtr = componentManager->CreateComponent<T>(this, std::forward<Args>(args)...);

    m_isDirty = true;

    return componentPtr;
}

template <typename T>
void Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    m_world->GetComponentManager()->RemoveComponent<T>(this);

    m_isDirty = true;
}

template <typename T>
T* Entity::GetComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    return m_world->GetComponentManager()->GetComponent<T>(this);
}

template <typename T>
bool Entity::HasComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    return m_world->GetComponentManager()->HasComponent<T>(this);
}

template <typename T>
T* Entity::GetComponentInParent(bool includeOwn /*= true*/)
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    if (includeOwn)
    {
        auto* comp = GetComponent<T>();
        if (comp)
            return comp;
    }

    if (m_parent && !m_parent->IsRootEntity())
    {
        return m_parent->GetComponentInParent<T>(true);
    }

    return nullptr;
}
}  // namespace red