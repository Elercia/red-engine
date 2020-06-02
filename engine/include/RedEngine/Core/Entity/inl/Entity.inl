
#include <algorithm>
#include <cassert>
#include <string>

#include "../../../Debug/Debug.hpp"
#include "../../Components/ComponentManager.hpp"
#include "../World.hpp"

namespace red
{
template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto* componentManager = m_world->GetComponentManager();

    if (componentManager->HasComponent<T>(this))
    {
        RED_ERROR("The entity already have the requested component");
    }

    auto componentPtr = componentManager->CreateComponent<T>(this, std::forward<Args>(args)...);

    return componentPtr;
}

template <typename T>
void Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    m_world->GetComponentManager()->RemoveComponent<T>(this);
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
}  // namespace red
