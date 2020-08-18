#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/SubEngine.hpp"

#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Core/Application.hpp"

namespace red
{
Engine& GetRedInstance()
{
    static Engine s_engine;
    return s_engine;
}

void Engine::Init(const EngineInitDesc& initDesc)
{
    auto& instance = GetRedInstance();

    instance.m_initDesc = initDesc;
    instance.InitAllSubEngines(initDesc);
}

Application& Engine::GetApplication()
{
    if (m_application == nullptr)
    {
        m_application = std::make_unique<Application>();
    }

    return *m_application;
}

const red::EngineInitDesc& Engine::GetInitDesc() const { return m_initDesc; }

void Engine::InitAllSubEngines(const EngineInitDesc& initDesc)
{
    std::apply(
        [initDesc](auto&... tupleArgs) {
            ((void) ApplyInit(std::forward<decltype(tupleArgs)>(tupleArgs), initDesc), ...);
        },
        m_subEngines);
}
}  // namespace red
