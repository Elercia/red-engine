namespace red
{
template <class LevelType>
void Application::LoadLevel()
{
    static_assert(std::is_base_of_v<Level, LevelType>, "Load level must be a Level type");

    auto newLevel = std::make_unique<LevelType>(m_world.get());

    LoadLevel(std::move(newLevel));
}
}  // namespace red
