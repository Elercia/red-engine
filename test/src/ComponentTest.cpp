#include <RedEngine/Core/Entity/Entity.hpp>
#include <SystemTest.hpp>
#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

TEST_CASE("Component", "[ECS]")
{
    SECTION("Bulk add remove")
    {
        red::World world;
        std::vector<red::Entity*> entitiesWithMock1;
        for (int i = 0; i < 100; ++i)
        {
            auto entity = world.CreateEntity();
            entitiesWithMock1.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        std::vector<red::Entity*> entitiesWithMock2;
        for (int i = 0; i < 100; ++i)
        {
            auto entity = world.CreateEntity();
            entitiesWithMock2.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        SECTION("Add/Remove components")
        {
            for (auto entity : entitiesWithMock1)
            {
                auto component = entity->AddComponent<MockComponent1>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->HasComponent<MockComponent1>());
                REQUIRE(entity->GetComponent<MockComponent1>() == component);
            }

            for (auto entity : entitiesWithMock2)
            {
                auto component = entity->AddComponent<MockComponent2>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->HasComponent<MockComponent2>());
                REQUIRE(entity->GetComponent<MockComponent2>() == component);

                // Check that entity don't have mock2
                REQUIRE_FALSE(entity->HasComponent<MockComponent1>());
            }

            for (auto entity : entitiesWithMock1)
            {
                entity->RemoveComponent<MockComponent1>();

                // Check that entity don't have mock1 or mock2
                REQUIRE_FALSE(entity->HasComponent<MockComponent1>());
                REQUIRE_FALSE(entity->HasComponent<MockComponent2>());
            }
        }

        SECTION("Component management")
        {
            for (auto& entity : entitiesWithMock1)
            {
                entity->AddComponent<MockComponent1>();
                REQUIRE(entity->HasComponent<MockComponent1>());

                entity->RemoveComponent<MockComponent1>();
                REQUIRE_FALSE(entity->HasComponent<MockComponent1>());

                entity->AddComponent<MockComponent1>();
                REQUIRE(entity->HasComponent<MockComponent1>());
            }
        }
    }

    SECTION("Check component validity")
    {
        red::World world;

        auto* entityA = world.CreateEntity();
        REQUIRE(entityA != nullptr);

        auto* componentAddedA = entityA->AddComponent<MockComponent1>();
        REQUIRE(componentAddedA != nullptr);

        auto* entityB = world.CreateEntity();
        REQUIRE(entityB != nullptr);

        auto* componentAddedB = entityB->AddComponent<MockComponent1>();
        REQUIRE(componentAddedB != nullptr);

        auto* componentGettedA = entityA->GetComponent<MockComponent1>();
        auto* componentGettedB = entityB->GetComponent<MockComponent1>();

        REQUIRE(componentAddedA != componentAddedB);
        REQUIRE(componentGettedA != componentGettedB);
        REQUIRE(componentGettedA == componentAddedA);
        REQUIRE(componentGettedB == componentAddedB);
    }
}

TEST_CASE("Persistent entity", "[ECS]")
{
    red::World world;

    auto* entityA = world.CreateEntity();
    REQUIRE(entityA != nullptr);
    REQUIRE(entityA->GetId() == red::MaxPersistentEntities);

    auto* componentAddedA = entityA->AddComponent<MockComponent1>();
    REQUIRE(componentAddedA != nullptr);

    entityA->SetPersistent(true);
    REQUIRE(entityA->GetId() <= red::MaxPersistentEntities);

    auto* componentGettedA = entityA->GetComponent<MockComponent1>();
    REQUIRE(componentAddedA == componentGettedA);
}
