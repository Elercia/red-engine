
#include <algorithm>
#include <cassert>
#include <string>
#include "../../debug/Debug.hpp"
#include "../ComponentManager.hpp"
#include "../World.hpp"

namespace red
{
template <typename T, typename... Args>
std::shared_ptr<T> Entity::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    if (HasComponent<T>())
    {
        RED_ERROR("The entity already have the requested component");
    }

    auto componentPtr = m_world->GetComponentManager()->CreateComponent<T>(this);

    m_components.insert(componentPtr);

    return componentPtr;
}

template <typename T>
void Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto componentIt = std::find_if(m_components.begin(), m_components.end(),
                                    [this](const std::shared_ptr<Component>& sharedPtr) {
                                        return sharedPtr->GetComponentName() == T::ComponentName;
                                    });

    m_components.erase(componentIt);

    m_world->GetComponentManager()->RemoveComponent<T>(this);
}

template <typename T>
std::shared_ptr<T> Entity::GetComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto component = std::find_if(m_components.begin(), m_components.end(),
                                  [this](const std::shared_ptr<Component>& comp) {
                                      return comp->GetComponentName() == T::ComponentName;
                                  });

    if (component == m_components.end())
        RED_ERROR("The entity doesn't have the requested component");

    return component;
}

template <typename T>
bool Entity::HasComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto component = std::find_if(m_components.begin(), m_components.end(),
                                  [this](const std::shared_ptr<Component>& sharedPtr) {
                                      return sharedPtr->GetComponentName() == T::ComponentName;
                                  });

    if (component == m_components.end())
        return false;

    return true;
}
}  // namespace red
