#include "TestModule.hpp"

#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"

#include <SystemTest.hpp>

RED_COMPONENT_BASIC_FUNCTIONS_IMPL(MockComponent1)
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(MockComponent11)
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(MockComponent2)

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Component", "[ECS]")
{
    SECTION("Bulk add remove")
    {
        red::World world;

        world.RegisterComponentType<MockComponent1>();
        world.RegisterComponentType<MockComponent11>();
        world.RegisterComponentType<MockComponent2>();

        std::vector<red::Entity*> entitiesWithMock1;
        for (int i = 0; i < 100; ++i)
        {
            auto* entity = world.CreateWorldEntity();
            entitiesWithMock1.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        std::vector<red::Entity*> entitiesWithMock2;
        for (int i = 0; i < 100; ++i)
        {
            auto* entity = world.CreateWorldEntity();
            entitiesWithMock2.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        SECTION("Add/Remove components")
        {
            for (auto* entity : entitiesWithMock1)
            {
                auto* component = entity->AddComponent<MockComponent1>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->HasComponent<MockComponent1>());
                REQUIRE(entity->GetComponent<MockComponent1>() == component);
            }

            for (auto* entity : entitiesWithMock2)
            {
                auto* component = entity->AddComponent<MockComponent2>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->HasComponent<MockComponent2>());
                REQUIRE(entity->GetComponent<MockComponent2>() == component);

                // Check that entity don't have mock2
                REQUIRE_FALSE(entity->HasComponent<MockComponent1>());
            }

            for (auto* entity : entitiesWithMock1)
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

        world.RegisterComponentType<MockComponent1>();
        world.RegisterComponentType<MockComponent11>();
        world.RegisterComponentType<MockComponent2>();

        auto* entityA = world.CreateWorldEntity();
        REQUIRE(entityA != nullptr);

        auto* componentAddedA = entityA->AddComponent<MockComponent1>();
        REQUIRE(componentAddedA != nullptr);

        auto* entityB = world.CreateWorldEntity();
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

TEST_CASE("Component inheritance", "[ECS]")
{
    red::World world;

    world.RegisterComponentType<MockComponent1>();
    world.RegisterComponentType<MockComponent11>();

    auto* entityA = world.CreateWorldEntity();
    REQUIRE(entityA != nullptr);

    SECTION("Hierarchy working")
    {
        auto* componentAddedA = entityA->AddComponent<MockComponent11>();
        REQUIRE(componentAddedA != nullptr);

        auto* componentGettedA = entityA->GetComponent<MockComponent1>();
        REQUIRE(componentAddedA == componentGettedA);

        REQUIRE(entityA->RemoveComponent<MockComponent1>());
        REQUIRE(entityA->GetComponent<MockComponent1>() == nullptr);
    }

    SECTION("Inverse hierarchy not working")
    {
        auto* componentAddedA = entityA->AddComponent<MockComponent1>();
        REQUIRE(componentAddedA != nullptr);

        auto* mock11 = entityA->GetComponent<MockComponent11>();
        REQUIRE(mock11 == nullptr);

        REQUIRE(entityA->RemoveComponent<MockComponent11>() == false);
        REQUIRE(entityA->GetComponent<MockComponent1>() != nullptr);
        REQUIRE(entityA->RemoveComponent<MockComponent1>());
        REQUIRE(entityA->GetComponent<MockComponent1>() == nullptr);
    }
}
