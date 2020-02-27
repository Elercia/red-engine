#pragma once

#include <RedEngine/ecs/Component.hpp>
#include <RedEngine/ecs/System.hpp>
#include <RedEngine/ecs/World.hpp>

class MockComponent1 : public red::Component
{
    RED_COMPONENT('MOC2')
public:
    MockComponent1(red::Entity* entity) : red::Component(entity) {}
};

class MockComponent2 : public red::Component
{
    RED_COMPONENT('MOC1')
public:
    MockComponent2(red::Entity* entity) : red::Component(entity) {}
};

class MockSystem : public red::System
{
public:
    MockSystem(red::World* world) : System(world) {}

    virtual void Update(float deltaTime)
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