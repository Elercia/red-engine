#pragma once

#include "RedEngine/Core/Entity/Components/Component.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/World.hpp"

class MockComponent1;
class MockComponent11;
class MockComponent2;

class MockComponent1 : public red::Component
{
public:
    explicit MockComponent1(red::Entity* entity) : red::Component(entity) {}
};

class MockComponent11 : public MockComponent1
{
public:
    explicit MockComponent11(red::Entity* entity) : MockComponent1(entity)
    {
    }
};

class MockComponent2 : public red::Component
{
public:
    explicit MockComponent2(red::Entity* entity) : red::Component(entity) {}
};

class MockSystem : public red::System
{
public:
    explicit MockSystem(red::World* world) : red::System(world) {}
    virtual ~MockSystem() = default;

    void Update() override
    {
        m_hasBeenUpdated = true;

        m_entityCount += (int)GetComponents<MockComponent1, MockComponent2>().size();
    }

    int m_entityCount = 0;
    bool m_hasBeenUpdated = false;
};