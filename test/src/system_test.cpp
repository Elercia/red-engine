#include <catch2/catch.hpp>
#include <system_test.hpp>

#include <iostream>

TEST_CASE( "System", "[System]" ) {

    red::World world;
    size_t baseSystemCount = world.GetSystems().size();
    std::shared_ptr<MockSystem> mockSystemPtr = world.AddSystem<MockSystem>();

    SECTION( "Adding mock system" ) {

        REQUIRE(world.GetSystems().size() == (baseSystemCount + 1));
        REQUIRE(mockSystemPtr != nullptr);
    }

    SECTION("Update world update systems") {

        world.Update(0.f);

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
    }

    SECTION("System fetch good entities") {

        auto e1 = world.CreateEntity();
        auto e2 = world.CreateEntity();
        auto e3 = world.CreateEntity();

        e1->AddComponent<MockComponent1>();
        e2->AddComponent<MockComponent1>();

        e2->AddComponent<MockComponent2>();
        e3->AddComponent<MockComponent2>();

        world.Update(0.f);

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
        REQUIRE(mockSystemPtr->m_entityCount == 1); // only e2 has the right components types
    }
}