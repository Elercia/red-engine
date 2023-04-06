
namespace red
{
template <typename S, typename ...Args>
SystemGraphStageBuilder& SystemGraphStageBuilder::AddSystem(Args&&... args)
{
    BaseSystem* system = m_world->AddSystem<S>(std::forward<Args>(args)...);

    return AddSystem(system);
}
}  // namespace red