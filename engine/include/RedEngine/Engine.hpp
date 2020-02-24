#pragma once

#include <memory>

#include <RedEngine/EngineConfig.hpp>
#include <RedEngine/engine/RenderingEngine.hpp>
#include <RedEngine/memory/MemoryManager.hpp>

namespace red
{
class Entity;

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

    static Engine& GetInstance();

private:
    MemoryManager m_memoryManager;
    RenderingEngine m_renderingEngine;
};

} // namespace red

red::Engine& GetRedInstance();
