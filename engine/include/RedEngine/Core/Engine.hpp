#pragma once

#include "RedEngine/Core/Debug/Logger/Logger.hpp"

#include <string_view>
#include <type_traits>

namespace red
{
class World;

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

    virtual bool RegisterComponentTypes();

protected:
    int m_argc;
    char** m_argv;

    World* m_world;

private:
    static Engine* s_engine;
};

}  // namespace red

#include "inl/Engine.inl"
