#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Thread/Thread.hpp"

#include <string_view>
#include <type_traits>

namespace red
{
class World;

constexpr uint32 RED_DEFAULT_FRAMEALLOCATOR_SIZE = 50 * 1024 * 1024;  // 10 Mo

class Engine
{
public:
    template <typename EngineClass>
    friend EngineClass* CreateEngineFrom(int argc, char** argv);

    static Engine* GetInstance();

public:
    Engine();
    virtual ~Engine();

    void MainLoop();

    virtual bool Create();
    virtual bool Destroy();

    virtual std::string_view GetGameName() const;

    virtual bool RegisterComponentTypes();

    virtual void SetupLogger();
    void InitAllocator();

    DoubleLinearAllocator& GetThreadFrameAllocator(int threadIndex);

    ThreadScheduler& GetScheduler();

protected:
    int m_argc;
    char** m_argv;

    World* m_world;

    DoubleLinearAllocator* m_frameAllocator;  // dynamic array initialized when the threading system is init

    ThreadScheduler m_scheduler;

    Logger::OutputDelegate::FuncIndex m_standarOutputFuncIndex;
    Logger::OutputDelegate::FuncIndex m_debugOutputFuncIndex;

private:
    static Engine* s_engine;
};

}  // namespace red

#include "inl/Engine.inl"
