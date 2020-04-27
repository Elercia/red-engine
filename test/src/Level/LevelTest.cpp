#include <catch2/catch.hpp>
#include <RedEngine/Application/Application.hpp>
#include "LevelTest.hpp"

TEST_CASE("Level changer", "[LEVEL]")
{
    red::Application app;

    app.LoadLevel<LevelTest1>();

    auto& world = app.GetWorld();
    REQUIRE(world.GetEntities().size() == 11);

    app.LoadLevel<LevelTest2>();

    REQUIRE(world.GetEntities().size() == 1);

    app.LoadLevel<LevelTest2>();

    REQUIRE(world.GetEntities().size() == 1);
}