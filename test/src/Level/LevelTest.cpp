#include <catch2/catch.hpp>
#include <RedEngine/Core/Application.hpp>
#include "LevelTest.hpp"

TEST_CASE("Level changer", "[LEVEL]")
{
    red::Application& app = red::GetRedInstance().GetApplication();
    auto* world = app.GetWorld();

    app.LoadLevel<LevelTest1>();

    REQUIRE(world->GetEntities().size() ==
            13);  // 10 entities + 1 persistent entity + 1 singleton entity + 1 root

    app.LoadLevel<LevelTest2>();

    REQUIRE(world->GetEntities().size() == 5);  // 1 persistent entity (from the last level) + 1
                                                // singleton entity + 1 root + 1 entity with 1 child

    app.LoadLevel<LevelTest2>();

    REQUIRE(world->GetEntities().size() ==
            7);  // 1 persistent entity (from the last level) + 1 singleton entity + 1 root + 1
                 // entity with 1 child + 1 entity with 1 child (from last level)
}