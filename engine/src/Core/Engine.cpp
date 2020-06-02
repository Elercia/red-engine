#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/SubEngine.hpp"

#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"
#include "RedEngine/Core/Configuration/Configuration.hpp"

namespace red
{
Engine& GetRedInstance()
{
    static Engine s_engine;
    return s_engine;
}

void Engine::Init(const std::string_view& resourceFolder, int argc, char** argv)
{
    auto& instance = GetRedInstance();
    
    auto config = instance.Get<Configuration>();
    config->SetResourceFolder(resourceFolder);
    config->LoadConfigFile(std::string(resourceFolder).append("/config.ini")); // TODO Set the resource folder configuration
    config->ParseCommandLine(argc, argv);

    instance.InitAllSubEngines();
}

void Engine::InitAllSubEngines()
{
    std::apply(
        [](auto&... tupleArgs) {
            ((void) ApplyInit(std::forward<decltype(tupleArgs)>(tupleArgs)), ...);
        },
        m_subEngines);
}
}  // namespace red
