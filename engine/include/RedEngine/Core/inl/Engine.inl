
namespace red
{
template <typename EngineClass>
EngineClass* CreateEngineFrom(int argc, char** argv)
{
    static_assert(std::is_base_of<Engine, EngineClass>::value,
                  "CreateEngineFrom called on a non-Engine class");

    SetLogLevel(LogLevel::LEVEL_DEBUG);

    static EngineClass engine;
    Engine::s_engine = &engine;

    engine.m_argc = argc;
    engine.m_argv = argv;

    bool created = engine.Create();

    if (!created)
    {
        RED_LOG_ERROR("Error creating the engine class");
        return nullptr;
    }

    return &engine;
}
}  // namespace red