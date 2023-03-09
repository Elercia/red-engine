namespace red
{
template <class T, class... Args>
T* World::AddSystem(Args&&... args)
{
    static_assert(std::is_base_of<BaseSystem, T>::value, "World AddSystem template T must be subclass of System");

    auto info = TypeInfo<T>();

    T* ptr = new T(this, std::forward<Args>(args)...);
    ptr->SetTraits(info);

    RED_LOG_INFO("Adding {} system", info.name);

    m_systems.push_back(ptr);
    m_addedSystems.push_back(ptr);

    return ptr;
}

template <class T>
bool World::RemoveSystem()
{
    static_assert(std::is_base_of<BaseSystem, T>::value, "World RemoveSystem template T must be subclass of System");

    auto info = TypeInfo<T>();
    auto systemTypeId = info.typeId;

    RED_LOG_INFO("Remove {} system", info.name);

    for (Array<BaseSystem*>::iterator it = m_systems.begin(), end = m_systems.end(); it != end; ++it)
    {
        BaseSystem* system = (*it);
        if (system->GetTypeTraits().typeId == systemTypeId)
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
    static_assert(std::is_base_of<BaseSystem, T>::value, "World GetSystem template T must be subclass of System");

    auto systemTypeId = TypeInfo<T>().typeId;
    for (auto* system : m_systems)
    {
        if (system->GetTypeTraits().typeId == systemTypeId)
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
    static_assert(!std::is_polymorphic<T>::value, "RegisterComponentType called with a component that is virtual. This is not allowed");

    auto type = TypeInfo<T>();
    auto [inserted, compData] = m_componentRegistry->CreateNewComponentTraits(type.typeId);

    // component may have been already registered
    if (inserted)
    {
        compData->componentTypeTraits = type;
        compData->creator = [=](Entity* owner)
        {
            auto comp = new T(owner);
            comp->m_typeTraits = type;
            return comp;
        };
        RegisterMembers<T>(*compData);
    }

    return true;
}

}  // namespace red
