#include <catch2/catch.hpp>
#include "RedEngine/Resources/ResourceEngine.hpp"
#include "RedEngine/Level/LevelResourceLoader.hpp"

using namespace red;

TEST_CASE("LEVEL loading", "[Resource]")
{
    ResourceEngine engine;

    engine.RegisterResourceLoader(ResourceType::LEVEL, new LevelResourceLoader);

    auto* loader = engine.GetResourceLoader<LevelResourceLoader>();

    REQUIRE(loader != nullptr);

    auto level = loader->LoadResource("leveltest");

    REQUIRE(level != nullptr);
}