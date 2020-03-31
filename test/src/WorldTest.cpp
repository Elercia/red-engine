#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <catch2/catch.hpp>

TEST_CASE("World entity and system check", "[ECS]")
{
    red::World world;
    const size_t entityCountStart = world.GetEntities().size();

    SECTION("Adding entity")
    {
        int entityCreated = 100;
        for (int i = 0; i < entityCreated; i++)
        {
            world.CreateEntity();
        }

        REQUIRE(world.GetEntities().size() - entityCountStart == entityCreated);
    }
}