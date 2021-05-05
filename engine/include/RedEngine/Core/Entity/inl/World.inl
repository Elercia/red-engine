
namespace red
{
template <class T, class... Args>
T* World::AddSystem(Args... args)
{
    static_assert(std::is_base_of<System, T>::value, "World add system template T must be subclass of System");

    auto* ptr = new T(this, std::forward<Args>(args)...);

    ptr->SetTypeId(typeid(T).hash_code());

    m_systems.push_back(ptr);

    return ptr;
}

template <class T>
void World::RemoveSystem()
{
    // TODO implement
}

template <typename T>
void World::LoadLevel()
{
    ChangeLevel(new T(this));
}

template <class T>
T* World::GetSystem()
{
    auto systemTypeId = typeid(T).hash_code();
    for (auto* system : m_systems)
    {
        if (system->GetTypeId() == systemTypeId)
            return static_cast<T*>(system);
    }

    return nullptr;
}

template <class T>
T* World::GetSingletonComponent()
{
    return m_singletonEntity->GetComponent<T>();
}

}  // namespace red
