namespace red
{
template <class T, class... Args>
T* World::AddSystem(Args... args)
{
    static_assert(std::is_base_of<System, T>::value,
                  "World add system template T must be subclass of System");

    auto ptr = new T(this, std::forward<Args>(args)...);

    m_systems.push_back(ptr);

    return ptr;
}

template <class T>
void World::RemoveSystem()
{
    // TODO implement
}

}  // namespace red
