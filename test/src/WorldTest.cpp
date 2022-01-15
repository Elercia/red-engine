#include "TestModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/Level.hpp"

#include <catch2/catch.hpp>

using namespace red;

TEST_CASE("Create world entities", "[ECS]")
{
    World world;
    world.Init();
    
    const size_t entityCountStart = world.GetEntities().size();

    SECTION("Adding entity")
    {
        constexpr size_t entityCreated = 100;
        for (size_t i = 0; i < entityCreated; i++)
        {
            world.CreateWorldEntity();
        }

        REQUIRE(world.GetEntities().size() - entityCountStart == entityCreated);
    }
}

TEST_CASE("Create level entities", "[ECS]")
{
    SECTION("Adding entity before level init")
    {
        World world;
        world.Init();

        Level level("Test level", &world);

        const size_t entityCountStart = world.GetEntities().size();

        constexpr size_t entityCreated = 100;
        for (size_t i = 0; i < entityCreated; i++)
        {
            level.CreateEntity();
        }

        level.InternInit();

        REQUIRE(world.GetEntities().size() - entityCountStart == entityCreated);

        level.InternFinalize();
    }

    SECTION("Adding entity after level init")
    {
        World world;
        world.Init();

        Level level("Test level", &world);
        level.InternInit();

        const size_t entityCountStart = world.GetEntities().size();

        constexpr size_t entityCreated = 100;
        for (size_t i = 0; i < entityCreated; i++)
        {
            level.CreateEntity();
        }

        REQUIRE(world.GetEntities().size() - entityCountStart == entityCreated);

        level.InternFinalize();
    }
}