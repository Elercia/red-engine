#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/RedEngineBase.hpp"

#include <memory>
#include <string_view>
#include <tuple>
#include <type_traits>

namespace red
{
class World;

// template <typename EngineClass>
// EngineClass* CreateEngineFrom(int argc, char** argv);

class Engine
{
public:
    template <typename EngineClass>
    friend EngineClass* CreateEngineFrom(int argc, char** argv);

    static Engine* GetInstance();

public:
    Engine();
    virtual ~Engine();

    int MainLoop();

    virtual bool Create();
    virtual bool Destroy();

    virtual std::string_view GetGameName() const;

protected:
    int m_argc;
    char** m_argv;

    World* m_world;

private:
    static Engine* s_engine;
};
}  // namespace red

#include "inl/Engine.inl"
