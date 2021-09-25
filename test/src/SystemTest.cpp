#include "RedEngine/Core/Event/Component/EventsComponent.hpp"

#include <SystemTest.hpp>
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("System", "[ECS]")
{
    red::World world;
    world.RegisterComponentType<red::EventsComponent>();
    world.RegisterComponentType<MockComponent1>();
    world.RegisterComponentType<MockComponent2>();

    auto* e = world.CreateWorldEntity();
    e->AddComponent<red::EventsComponent>();

    size_t baseSystemCount = world.GetSystems().size();
    auto* mockSystemPtr = world.AddSystem<MockSystem>();

    SECTION("Adding mock system")
    {
        REQUIRE(world.GetSystems().size() == (baseSystemCount + 1));
        REQUIRE(mockSystemPtr != nullptr);
    }

    SECTION("Update world update Systems")
    {
        world.Update();

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
    }

    SECTION("System is fetching the right entities")
    {
        auto e1 = world.CreateWorldEntity();
        auto e2 = world.CreateWorldEntity();
        auto e3 = world.CreateWorldEntity();

        e1->AddComponent<MockComponent1>();
        e2->AddComponent<MockComponent1>();

        e2->AddComponent<MockComponent2>();
        e3->AddComponent<MockComponent2>();

        world.Update();

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
        REQUIRE(mockSystemPtr->m_entityCount == 1);  // only e2 has the right components types
    }
}