#pragma once

#include "EngineConfig.hpp"

#include "RedEngine/Core/Configuration/Configuration.hpp"
#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Event/EventSystem.hpp"
#include "RedEngine/Core/Memory/MemoryManager.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"

#include <memory>
#include <tuple>
#include <type_traits>

namespace red
{
class Application;

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

    static void Init(const EngineInitDesc& initDesc);

    Application& GetApplication();

    void RegisterResourceLoaders(ResourceEngine* resourceEngine);

    const EngineInitDesc& GetInitDesc() const;

private:
    void InitAllSubEngines(const EngineInitDesc& initDesc);

private:
    std::tuple<Configuration, Logger, MemoryManager, ResourceEngine, RenderingEngine, EventSystem> m_subEngines{};

    std::unique_ptr<Application> m_application;
    EngineInitDesc m_initDesc;
};

Engine& GetEngine();

template <class SubEngineType>
SubEngineType* GetSubEngine()
{
    return GetEngine().Get<SubEngineType>();
}

}  // namespace red
