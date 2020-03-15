#include <RedEngine/Engine.hpp>
#include <RedEngine/engine/RenderingEngine.hpp>
#include <RedEngine/log/Logger.hpp>

namespace red
{
Engine& Engine::GetInstance()
{
    static Engine s_instance;
    if (!s_instance.m_isInitialized)
    {
        s_instance.Init();
    }

    return s_instance;
}

Engine::Engine()
    : m_isInitialized(false), m_memoryManager(), m_renderingEngine(nullptr), m_logger(nullptr)
{
}

MemoryManager& Engine::GetMemoryManager() { return m_memoryManager; }

Engine::~Engine()
{
    delete m_renderingEngine;
    delete m_logger;

#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif  //  RED_ENABLE_MEMORY_PROFILING
}

RenderingEngine& Engine::GetRenderingEngine() { return *m_renderingEngine; }

Logger& Engine::GetLogger() { return *m_logger; }

void Engine::Init()
{
    m_isInitialized = true;

    auto renderingEngineMemory = m_memoryManager.Allocate(sizeof(RenderingEngine));
    m_renderingEngine = new (renderingEngineMemory) RenderingEngine;

    auto loggerMemory = m_memoryManager.Allocate(sizeof(Logger));
    m_logger = new (loggerMemory) Logger;
}
}  // namespace red

red::Engine& GetRedInstance() { return red::Engine::GetInstance(); }
