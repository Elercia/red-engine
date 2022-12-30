#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"

#include <string_view>
#include <type_traits>

namespace red
{
class World;

constexpr uint32 RED_DEFAULT_FRAMEALLOCATOR_SIZE = 10 * 1024 * 1024; // 10 Mo

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

    DoubleLinearAllocator& GetFrameAllocator();

protected:
    int m_argc;
    char** m_argv;

    World* m_world;

    DoubleLinearAllocator m_frameAllocator;

private:
    static Engine* s_engine;
};

}  // namespace red

#include "inl/Engine.inl"
