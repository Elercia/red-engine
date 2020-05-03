#pragma once

#include <RedEngine/Level/Level.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>

class LevelTest1 : public red::Level
{
public:
    LevelTest1() : red::Level("LevelTest1") {}

    void Init(red::World& world) override
    {
        for (int i = 0; i < 10; ++i)
        {
            world.CreateEntity();
        }

        auto* e = world.CreateEntity();
        e->SetPersistent(true);
    };

    void Finalize() override{};
};

class LevelTest2 : public red::Level
{
public:
    LevelTest2() : red::Level("LevelTest2") {}

    void Init(red::World& world) override{

    };
    void Finalize() override{};
};
