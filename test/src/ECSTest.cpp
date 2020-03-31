#include <ECSTest.hpp>
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("System", "[ECS]")
{
    red::World world;
    size_t baseSystemCount = world.GetSystems().size();
    MockSystem* mockSystemPtr = world.AddSystem<MockSystem>();

    SECTION("Adding mock system")
    {
        REQUIRE(world.GetSystems().size() == (baseSystemCount + 1));
        REQUIRE(mockSystemPtr != nullptr);
    }

    SECTION("Update world update Systems")
    {
        world.Update(0.F);

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
    }

    SECTION("System is fetching the right entities")
    {
        auto e1 = world.CreateEntity();
        auto e2 = world.CreateEntity();
        auto e3 = world.CreateEntity();

        e1->AddComponent<MockComponent1>();
        e2->AddComponent<MockComponent1>();

        e2->AddComponent<MockComponent2>();
        e3->AddComponent<MockComponent2>();

        world.Update(0.F);

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
        REQUIRE(mockSystemPtr->m_entityCount == 1);  // only e2 has the right components types
    }
}