#pragma once

#include <RedEngine/Level/Level.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Core/Debug/Logger/Logger.hpp>

class LevelTest1 : public red::Level
{
public:
    LevelTest1(red::World* world) : red::Level("LevelTest1", world) {}

    void Init() override
    {
        for (int i = 0; i < 10; ++i)
        {
            CreateEntity();
        }

        auto* e = CreateEntity();
        e->SetPersistent(true);
    };

    void Finalize() override{};
};

class LevelTest2 : public red::Level
{
public:
    LevelTest2(red::World* world) : red::Level("LevelTest2", world) {}

    void Init() override
    {
        auto* e = CreateEntity();
        e->SetPersistent(true);

        auto* c = CreateEntity();
        c->SetParent(e);
    };
    void Finalize() override{};
};
