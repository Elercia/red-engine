#include <RedEngine/Engine.hpp>
#include <RedEngine/memory/MemoryManager.hpp>

namespace red
{
Engine& Engine::GetInstance()
{
    static Engine s_instance;

    return s_instance;
}

Engine::Engine() : m_memoryManager()
{}

MemoryManager& Engine::GetMemoryManager()
{
    return m_memoryManager;
}

Engine::~Engine()
{
#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif //  RED_ENABLE_MEMORY_PROFILING
}
} // namespace red

red::Engine& GetRedInstance()
{
    return red::Engine::GetInstance();
}
