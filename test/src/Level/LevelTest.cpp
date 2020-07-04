#include <catch2/catch.hpp>
#include <RedEngine/Core/Application.hpp>
#include "LevelTest.hpp"

TEST_CASE("Level changer", "[LEVEL]")
{
    red::Application& app = red::GetRedInstance().GetApplication();

    app.LoadLevel<LevelTest1>();

    auto& world = app.GetWorld();
    REQUIRE(world.GetEntities().size() == 12); // 11 entities + 1 singleton entity

    app.LoadLevel<LevelTest2>();

    REQUIRE(world.GetEntities().size() == 2);// 1 entities + 1 singleton entity

    app.LoadLevel<LevelTest2>();

    REQUIRE(world.GetEntities().size() == 2);// 1 entities + 1 singleton entity
}