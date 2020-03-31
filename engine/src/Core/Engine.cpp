#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Debug/Logger/Logger.hpp"
#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"

namespace red
{
Engine& Engine::GetInstance()
{
    static Engine s_instance;

    return s_instance;
}

Engine::Engine() : m_memoryManager()
{
    auto renderingEngineMemory = m_memoryManager.Allocate(sizeof(RenderingEngine));  // FIXME
    m_renderingEngine = new (renderingEngineMemory) RenderingEngine;                 // FIXME

    auto resourceEngineMemory = m_memoryManager.Allocate(sizeof(ResourceEngine));  // FIXME
    m_resourceEngine = new (resourceEngineMemory) ResourceEngine;                  // FIXME

    auto loggerMemory = m_memoryManager.Allocate(sizeof(Logger));  // FIXME
    m_logger = new (loggerMemory) Logger;                          // FIXME
}

const MemoryManager& Engine::GetMemoryManager() { return m_memoryManager; }

Engine::~Engine()
{
    m_renderingEngine->~RenderingEngine();
    m_logger->~Logger();

#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif  //  RED_ENABLE_MEMORY_PROFILING
}

RenderingEngine* Engine::GetRenderingEngine() { return m_renderingEngine; }

Logger* Engine::GetLogger() { return m_logger; }

ResourceEngine* Engine::GetResourceEngine() { return m_resourceEngine; }
}  // namespace red

red::Engine& GetRedInstance() { return red::Engine::GetInstance(); }
