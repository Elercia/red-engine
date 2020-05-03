#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/SubEngine.hpp"

#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"

namespace red
{
Engine& GetRedInstance()
{
    static Engine s_engine;
    return s_engine;
}

void Engine::Init() { GetRedInstance().InitAllSubEngines(); }

void Engine::InitAllSubEngines()
{
    std::apply(
        [](auto&... tupleArgs) {
            ((void) ApplyInit(std::forward<decltype(tupleArgs)>(tupleArgs)), ...);
        },
        m_subEngines);
}
}  // namespace red
