namespace red
{
template <class T, class... Args>
T* World::AddSystem(Args&&... args)
{
    static_assert(std::is_base_of<System, T>::value, "World add system template T must be subclass of System");

    auto info = TypeInfo<T>();

    auto* ptr = new T(this, std::forward<Args>(args)...);
    ptr->SetTypeTraits(info);

    RED_LOG_INFO("Adding {} system", info.name);

    m_systems.push_back(ptr);

    return ptr;
}

template <class T>
bool World::RemoveSystem()
{
    auto info = TypeInfo<T>();
    auto systemTypeId = info.typeId;

    RED_LOG_INFO("Remove {} system", info.name);

    for (Array<System*>::iterator it = m_systems.begin(), end = m_systems.end(); it != end; ++it)
    {
        System* system = (*it);
        if (system->GetTypeId() == systemTypeId)
        {
            m_systems.erase(it);

            delete system;

            return true;
        }
    }

    return false;
}

template <typename T>
void World::LoadLevel()
{
    ChangeLevel(new T(this));
}

template <class T>
T* World::GetSystem()
{
    auto systemTypeId = TypeInfo<T>().typeId;
    for (auto* system : m_systems)
    {
        if (system->GetTypeId() == systemTypeId)
            return static_cast<T*>(system);
    }

    return nullptr;
}

template <typename T>
T* World::GetWorldComponent()
{
    for (auto* e : m_entities)
    {
        auto* comp = e->GetComponent<T>();
        if (comp != nullptr)
            return comp;
    }

    return nullptr;
}

template <typename T>
bool World::RegisterComponentType()
{
    static_assert(std::is_base_of<Component, T>::value, "RegisterComponentType called on non component type");

    auto [inserted, compData] = m_componentRegistry->CreateNewComponentTraits(TypeInfo<T>().typeId);

    // component may have been already registered
    if (inserted)
    {
        T::RegisterComponentTypeTraits(compData);

        if (compData->inheritedComponentTraits != EmptyTypeTraits &&
            compData->inheritedComponentTraits.name != "red::Component")
        {
            auto* inheritedCompTraits =
                m_componentRegistry->GetComponentTraitsInternal(compData->inheritedComponentTraits.typeId);

            if (inheritedCompTraits == nullptr)
            {
                RED_LOG_ERROR("Failed to find inherited component {}. Please make sure to register {} before {}",
                              compData->inheritedComponentTraits.name, compData->inheritedComponentTraits.name,
                              TypeInfo<T>().name);
                return false;
            }

            inheritedCompTraits->childComponentTraits.push_back(compData);
        }
    }

    return true;
}

}  // namespace red
