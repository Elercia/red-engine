namespace red
{
template <class T>
std::shared_ptr<T> World::AddSystem(...)
{
    static_assert(std::is_base_of<System, T>::value,
                  "World add system template T must be subclass of System");

    auto ptr =  std::make_shared<T>(this);

    m_systems.push_back(ptr);

    return ptr;
}

}  // namespace red
