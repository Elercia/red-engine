#include "RedEngine/Core/Entity/SystemExecutionGraph.hpp"

#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Thread/Thread.hpp"

namespace red
{
SystemGraphStageBuilder::SystemGraphStageBuilder(World* world) : m_world(world)
{
}

SystemGraphStageBuilder SystemGraphStageBuilder::NewStage(World* world)
{
    SystemGraphStageBuilder stage(world);

    return stage;
}

SystemGraphStageBuilder& SystemGraphStageBuilder::AddSystem(BaseSystem* system)
{
    for (const auto& readOnlyComp : system->GetROComponents())
    {
        if (m_readWriteComponents.Find(readOnlyComp) != m_readWriteComponents.npos)
        {
            RED_LOG_ERROR(
                "System {} use component {} with read-only mode but others system in the same execution stage use it "
                "in read-write mode",
                system->GetTypeTraits().name, readOnlyComp.name);
        }
    }

    for (const auto& readWriteComp : system->GetRWComponents())
    {
        if (m_readWriteComponents.Find(readWriteComp) != m_readWriteComponents.npos)
        {
            RED_LOG_ERROR(
                "System {} use component {} with read-write mode but others system in the same execution stage also "
                "use it with read-write mode",
                system->GetTypeTraits().name, readWriteComp.name);
        }
    }

    for (const auto& readWriteComp : system->GetRWComponents())
    {
        if (m_readOnlyComponents.Find(readWriteComp) != m_readWriteComponents.npos)
        {
            RED_LOG_ERROR(
                "System {} use component {} with read-write mode but others system in the same execution stage "
                "use it with read-only mode",
                system->GetTypeTraits().name, readWriteComp.name);
        }
    }

    for (const auto& readOnlyComp : system->GetROComponents())
    {
        m_readOnlyComponents.push_back(readOnlyComp);
    }

    for (const auto& readWriteComp : system->GetRWComponents())
    {
        m_readWriteComponents.push_back(readWriteComp);
    }

    m_systems.push_back(system);

    return *this;
}

std::function<void(void)> SystemGraphStageBuilder::Build()
{
    if (m_systems.size() == 1)
    {
        return 
            [cpy = std::move(m_systems)]()
            {
                for (auto* s : cpy)
                {
                    s->Update();
                }
            };
    }
    else
    {
        return 
            [cpy = std::move(m_systems)]()
            {
                auto& scheduler = Engine::GetInstance()->GetScheduler();
                WaitGroup wg(cpy.size());

                for (auto* s : cpy)
                {
                    scheduler.Schedule(
                        [=]()
                        {
                            s->Update();
                            wg.Done();
                        });
                }

                wg.Wait();
            };
    }
}
}  // namespace red