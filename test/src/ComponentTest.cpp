#include <ECSTest.hpp>
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("Component", "[ECS]")
{
    red::World world;
    auto entity = world.CreateEntity();
    REQUIRE(entity != nullptr);

    SECTION("Adding component")
    {
        auto component = entity->AddComponent<MockComponent1>();

        REQUIRE(component != nullptr);
        REQUIRE(entity->HasComponent<MockComponent1>());
    }
}