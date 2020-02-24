#include <RedEngine/Engine.hpp>
#include <RedEngine/memory/MemoryManager.hpp>

namespace red
{
Engine& Engine::GetInstance()
{
    static Engine s_instance;

    return s_instance;
}

Engine::Engine() : m_memoryManager(), m_renderingEngine() {}

MemoryManager& Engine::GetMemoryManager() { return m_memoryManager; }

Engine::~Engine()
{
#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif //  RED_ENABLE_MEMORY_PROFILING
}

RenderingEngine& Engine::GetRenderingEngine() { return m_renderingEngine; }
} // namespace red

red::Engine& GetRedInstance() { return red::Engine::GetInstance(); }
