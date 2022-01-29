#include "TestModule.hpp"
#include "LevelTest.hpp"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Level/JsonLevelNames.hpp"
#include "RedEngine/Level/JsonLevelSerializer.hpp"
#include "RedEngine/Utils/FileUtils.hpp"

#include <catch2/catch.hpp>

using namespace red;

TEST_CASE("Level serialisation", "[LEVEL]")
{
    World world;
    world.Init();

    Level level("SerializedLevel", &world);

    Entity* e1 = level.CreateEntity("Test");
    Entity* e2 = level.CreateEntity("Test2");
    e1->GetComponent<Transform>()->SetPosition({0.f, 10.f});
    e2->GetComponent<Transform>()->SetPosition({10.f, 0.f});

    Entity* child1 = level.CreateEntity("Test1", e1);
    level.CreateEntity("Test11", child1);

    level.InternInit();

    Path p = Path::Resource("tmp_out/test_serialize_level.json");

    JsonLevelSerializer serializer(&level);
    REQUIRE(serializer.Serialize(p));

    using json = nlohmann::json;
    json j = json::parse(red::ReadFile(p));

    REQUIRE(j[JsonNames::LEVEL_ENTITIES].size() == 2);

    auto e1json = j[JsonNames::LEVEL_ENTITIES][0];
    auto e2json = j[JsonNames::LEVEL_ENTITIES][1];

    REQUIRE(e1json[JsonNames::ENTITY_NAME] == "Test");
    REQUIRE(e2json[JsonNames::ENTITY_NAME] == "Test2");

    REQUIRE(e1json[JsonNames::ENTITY_ID] != e2json[JsonNames::ENTITY_ID]);

    REQUIRE(e1json[JsonNames::ENTITY_COMPONENTS].size() == 1);
    REQUIRE(e2json[JsonNames::ENTITY_COMPONENTS].size() == 1);

    REQUIRE(e1json[JsonNames::ENTITY_COMPONENTS]["red::Transform"]["position"] == Serialize(Vector2(0.f, 10.f)));
    REQUIRE(e2json[JsonNames::ENTITY_COMPONENTS]["red::Transform"]["position"] == Serialize(Vector2(10.f, 0.f)));

    REQUIRE(e1json[JsonNames::ENTITY_CHILDREN].size() == 1);
    REQUIRE(e2json[JsonNames::ENTITY_CHILDREN].empty());

    REQUIRE(e1json[JsonNames::ENTITY_CHILDREN][0][JsonNames::ENTITY_CHILDREN].size() == 1);

    REQUIRE(e1json[JsonNames::ENTITY_CHILDREN][0][JsonNames::ENTITY_NAME] == "Test1");
    REQUIRE(e1json[JsonNames::ENTITY_CHILDREN][0][JsonNames::ENTITY_CHILDREN][0][JsonNames::ENTITY_NAME] == "Test11");

    level.InternFinalize();
}

TEST_CASE("Level deserialisation", "[LEVEL]")
{
}