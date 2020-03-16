#include <RedEngine/Engine.hpp>
#include <RedEngine/memory/MemoryManager.hpp>
#include <RedEngine/log/Logger.hpp>

namespace red
{
Engine& Engine::GetInstance()
{
    static Engine s_instance;

    return s_instance;
}

Engine::Engine() : m_memoryManager(), m_renderingEngine(), m_logger(new Logger()) {}

MemoryManager& Engine::GetMemoryManager() { return m_memoryManager; }

Engine::~Engine()
{
#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif //  RED_ENABLE_MEMORY_PROFILING

    delete m_logger;
}

RenderingEngine& Engine::GetRenderingEngine() { return m_renderingEngine; }

Logger& Engine::GetLogger() { return *m_logger; }
} // namespace red

red::Engine& GetRedInstance() { return red::Engine::GetInstance(); }
