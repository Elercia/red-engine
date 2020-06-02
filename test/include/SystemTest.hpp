#pragma once

#include <RedEngine/Core/Components/Component.hpp>
#include <RedEngine/Core/Entity/System.hpp>
#include <RedEngine/Core/Entity/World.hpp>

class MockComponent1 : public red::Component
{
public:
    explicit MockComponent1(red::Entity* entity) : red::Component(entity) {}
};

class MockComponent2 : public red::Component
{
public:
    explicit MockComponent2(red::Entity* entity) : red::Component(entity) {}
};

class MockSystem : public red::System
{
public:
    explicit MockSystem(red::World* world) : System(world) {}

    void Update() override
    {
        m_hasBeenUpdated = true;

        for (auto& entity : GetComponents<MockComponent1, MockComponent2>())
        {
            m_entityCount++;
        }
    }

    int m_entityCount = 0;
    bool m_hasBeenUpdated = false;
};