#pragma once

#include "RedEngine/Core/Entity/World.hpp"

#include <functional>

namespace red
{
class BaseSystem;

class SystemGraphStageBuilder
{
public:
    static SystemGraphStageBuilder NewStage(World* world);

    template <typename S, typename... Args>
    SystemGraphStageBuilder& AddSystem(Args&&... args);
    SystemGraphStageBuilder& AddSystem(BaseSystem* system);

    std::function<void(void)> Build();

private:
    SystemGraphStageBuilder(World* world);

private:
    World* m_world;
    Array<BaseSystem*> m_systems;

    Array<TypeTraits> m_readOnlyComponents;
    Array<TypeTraits> m_readWriteComponents;
};
}  // namespace red

#include "inl/SystemExecutionGraph.inl"