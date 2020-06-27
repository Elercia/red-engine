
#include <RedEngine/Debug/System/DebugSystem.hpp>
#include <RedEngine/Debug/Component/DebugComponent.hpp>
#include <RedEngine/Core/Engine.hpp>

namespace red
{
DebugSystem::DebugSystem(World* world)
    : System(world), m_renderingEngine(GetRedSubEngine<RenderingEngine>())
{
}

void DebugSystem::LateUpdate()
{
    auto* debugComp = GetSingletonEntity().GetComponent<DebugComponent>();

    for (auto& line : debugComp->m_frameDebugLines)
    {
        m_renderingEngine->DrawLine(line.first, line.second);
    }

    debugComp->m_frameDebugLines.clear();
}
}  // namespace red
