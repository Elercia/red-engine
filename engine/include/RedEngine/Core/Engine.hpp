#pragma once

#include <memory>
#include <tuple>
#include <type_traits>

#include <RedEngine/Event/EventSystem.hpp>
#include "../Memory/MemoryManager.hpp"
#include "../Core/Configuration/Configuration.hpp"
#include "../Debug/Logger/Logger.hpp"
#include "../Resources/ResourceEngine.hpp"
#include "../Rendering/RenderingEngine.hpp"
#include "EngineConfig.hpp"

namespace red
{
/// The engine regroup all the singletons class that are needed by the engine
/// The placement order in the struct define the creation order, and so the dependencies
class Engine
{
public:
    template <class SubEngineType>
    SubEngineType* Get()
    {
        return &(std::get<SubEngineType>(m_subEngines));
    }

    static void Init(const std::string_view& resourceFolder, int argc, char** argv);

private:
    std::tuple<Configuration, Logger, MemoryManager, ResourceEngine, RenderingEngine, EventSystem>
        m_subEngines{};

    void InitAllSubEngines();
};

Engine& GetRedInstance();

template <class SubEngineType>
SubEngineType* GetRedSubEngine()
{
    return GetRedInstance().Get<SubEngineType>();
}

}  // namespace red
