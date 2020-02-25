#include <catch2/catch.hpp>
#include <RedEngine/ecs/World.hpp>
#include <RedEngine/ecs/Entity.hpp>


TEST_CASE( "World entity and system check", "[World]" ) {

    red::World world;
    const size_t entityCountStart = world.GetEntities().size();

    SECTION( "Adding entity" ) {

        int entityCreated = 100;
        for (int i = 0; i < entityCreated; i++)
        {
            world.CreateEntity();
        }

        REQUIRE( world.GetEntities().size() - entityCountStart == entityCreated );
    }
}