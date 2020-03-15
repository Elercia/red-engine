#pragma once

#include <memory>

#include <RedEngine/EngineConfig.hpp>
#include <RedEngine/memory/MemoryManager.hpp>

namespace red
{
class Entity;
class RenderingEngine;
class Logger;

class Engine final
{
public:
    Engine();
    Engine(const Engine&) = delete;
    Engine(Engine&&) = default;
    ~Engine();

    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = default;

    MemoryManager& GetMemoryManager();

    RenderingEngine& GetRenderingEngine();

    Logger& GetLogger();

    static Engine& GetInstance();

private:
    void Init();
    bool m_isInitialized;

    MemoryManager m_memoryManager;
    RenderingEngine *m_renderingEngine;
    Logger *m_logger;
};

}  // namespace red

red::Engine& GetRedInstance();
