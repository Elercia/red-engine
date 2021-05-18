#include <catch2/catch.hpp>
#include "RedEngine/Resources/ResourceHolderComponent.hpp"
#include "RedEngine/Level/LevelResourceLoader.hpp"

using namespace red;

TEST_CASE("LEVEL loading", "[Resource]")
{
    World w;
    Entity* e = w.CreateEntity("test");
    ResourceHolderComponent* resourceHolderComp = e->AddComponent<ResourceHolderComponent>();

    resourceHolderComp->RegisterResourceLoader(ResourceType::LEVEL, new LevelResourceLoader(&w));

    auto* loader = resourceHolderComp->GetResourceLoader<LevelResourceLoader>();

    REQUIRE(loader != nullptr);

    auto level = loader->LoadResource("leveltest");

    //REQUIRE(level != nullptr);
}