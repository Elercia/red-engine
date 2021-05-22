#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <memory>
#include <tuple>
#include <type_traits>

namespace red
{
class World;

// template <typename EngineClass>
// EngineClass* CreateEngineFrom(int argc, char** argv);

class Engine
{
    template <typename EngineClass>
    friend EngineClass* CreateEngineFrom(int argc, char** argv);

public:
    Engine();
    virtual ~Engine();

    int MainLoop();

    virtual bool Create() = 0;
    virtual bool Destroy() = 0;

    virtual bool RegisterComponentTypes();

private:
    bool InternalCreate();
    bool InternalDestroy();

protected:
    int m_argc;
    char** m_argv;

    World* m_world;
};

}  // namespace red

#include "inl/Engine.inl"
