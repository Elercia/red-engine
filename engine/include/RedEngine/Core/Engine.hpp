#pragma once

#include <memory>

#include "../Memory/MemoryManager.hpp"
#include "EngineConfig.hpp"

namespace red
{
class Entity;
class RenderingEngine;
class ResourceEngine;
class Logger;
class Configuration;

class Engine final
{
public:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) = default;
    ~Engine();

    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = default;

    const MemoryManager& GetMemoryManager();

    RenderingEngine* GetRenderingEngine();
    ResourceEngine* GetResourceEngine();
    Logger* GetLogger();

    static Engine& GetInstance();

private:
    MemoryManager m_memoryManager;
    RenderingEngine* m_renderingEngine;
    ResourceEngine* m_resourceEngine;
    Logger* m_logger;

    static Engine* s_instance;
};

}  // namespace red

red::Engine& GetRedInstance();
