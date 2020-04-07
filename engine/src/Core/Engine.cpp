#include "RedEngine/Core/Engine.hpp"

#include "RedEngine/Rendering/RenderingEngine.hpp"
#include "RedEngine/Resources/ResourceEngine.hpp"

namespace red
{
Engine* Engine::s_instance;

Engine& Engine::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new Engine;
    }
    return *s_instance;
}

Engine::Engine() : m_memoryManager()
{
    m_renderingEngine = new RenderingEngine;
    m_resourceEngine = new ResourceEngine;
}

const MemoryManager& Engine::GetMemoryManager() { return m_memoryManager; }

Engine::~Engine()
{
    delete m_resourceEngine;
    delete m_renderingEngine;

#ifdef RED_ENABLE_MEMORY_PROFILING
    GetRedInstance().GetMemoryManager().DumpMemory();
#endif  //  RED_ENABLE_MEMORY_PROFILING
}

RenderingEngine* Engine::GetRenderingEngine() { return m_renderingEngine; }

ResourceEngine* Engine::GetResourceEngine() { return m_resourceEngine; }
}  // namespace red

red::Engine& GetRedInstance() { return red::Engine::GetInstance(); }
