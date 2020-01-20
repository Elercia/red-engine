#pragma once

#include <OgreRoot.h>
#include <RedEngine/EngineConfig.hpp>
#include <RedEngine/memory/MemoryManager.hpp>
#include <memory>

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

    static Engine& GetInstance();

private:
    MemoryManager m_memoryManager;
};

} // namespace red

red::Engine& GetRedInstance();
