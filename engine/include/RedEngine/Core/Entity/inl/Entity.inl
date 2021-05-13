
namespace red
{
template <typename T, typename... Args>
T* Entity::AddComponent(Args&&... args)
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    auto* componentManager = GetComponentManager();

    if (componentManager->HasComponent<T>(this))
    {
        RED_LOG_WARNING("Entity {} already has the component {}", m_name, typeid(T).name());
        return componentManager->GetComponent<T>(this);
    }

    auto componentPtr = componentManager->CreateComponent<T>(this, std::forward<Args>(args)...);

    m_isDirty = true;

    return componentPtr;
}

template <typename T>
void Entity::RemoveComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    GetComponentManager()->RemoveComponent<T>(this);

    m_isDirty = true;
}

template <typename T>
T* Entity::GetComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    return GetComponentManager()->GetComponent<T>(this);
}

template <typename T>
bool Entity::HasComponent()
{
    static_assert(std::is_base_of<Component, T>::value, "T is not a Component type");

    return GetComponentManager()->HasComponent<T>(this);
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