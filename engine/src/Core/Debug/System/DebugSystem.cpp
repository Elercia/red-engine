
#include <RedEngine/Core/Debug/System/DebugSystem.hpp>
#include <RedEngine/Core/Debug/Component/DebugComponent.hpp>
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

    // TODO move this to the rendering engine
    for (auto& line : debugComp->m_frameDebugLines)
    {
        m_renderingEngine->DrawLine(line.first, line.second);
    }

    debugComp->m_frameDebugLines.clear();

    //TODO add the management of the in-game console and debug facilities like speeding the game and fullscreen control
}
}  // namespace red
