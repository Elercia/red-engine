#pragma once

#include <RedEngine/Level/Level.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Debug/Logger/Logger.hpp>

class LevelTest1 : public red::Level
{
public:
    LevelTest1() : red::Level("LevelTest1") {}

    void Init() override
    {
        for (int i = 0; i < 10; ++i)
        {
            m_world->CreateEntity();
        }

        auto* e = m_world->CreateEntity();
        e->SetPersistent(true);
    };

    void Finalize() override{};
};

class LevelTest2 : public red::Level
{
public:
    LevelTest2() : red::Level("LevelTest2") {}

    void Init() override{

    };
    void Finalize() override{};
};
