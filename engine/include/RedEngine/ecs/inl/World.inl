namespace red
{
template <class T>
std::shared_ptr<T> World::AddSystem(...)
{
    static_assert(std::is_base_of<System, T>::value,
                  "World add system template T must be subclass of System");

    return std::make_shared<T>(this);
}

}  // namespace red
