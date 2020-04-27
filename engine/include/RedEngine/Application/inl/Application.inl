namespace red
{
template <class LevelType>
void Application::LoadLevel()
{
    if (m_level != nullptr)
    {
        m_level->Finalize();
    }

    m_level.reset(new LevelType());

    m_level->Init();
}
}  // namespace red
