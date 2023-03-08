#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Utils/SystemInfo.hpp"

#include <catch2/catch.hpp>
#include <vector>

#include "EngineTest.hpp"
#include "SystemTest.hpp"
#include "TestModule.hpp"

TEST_CASE("Component", "[ECS]")
{
    SECTION("Bulk add remove")
    {
        red::InitSystemInfo();

        red::World world;
        world.Init();

        world.RegisterComponentType<MockComponent1>();
        world.RegisterComponentType<MockComponent11>();
        world.RegisterComponentType<MockComponent2>();

        std::vector<red::Entity*> entitiesWithMock1;
        for (int i = 0; i < 100; ++i)
        {
            auto* entity = world.CreateWorldEntity("a");
            entitiesWithMock1.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        std::vector<red::Entity*> entitiesWithMock2;
        for (int i = 0; i < 100; ++i)
        {
            auto* entity = world.CreateWorldEntity("b");
            entitiesWithMock2.push_back(entity);
            REQUIRE(entity != nullptr);
        }

        SECTION("Add/Remove components")
        {
            for (auto* entity : entitiesWithMock1)
            {
                auto* component = entity->AddComponent<MockComponent1>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->GetComponent<MockComponent1>() == component);
            }

            for (auto* entity : entitiesWithMock2)
            {
                auto* component = entity->AddComponent<MockComponent2>();

                REQUIRE(component != nullptr);
                REQUIRE(entity->GetComponent<MockComponent2>() == component);

                // Check that entity don't have mock2
                REQUIRE_FALSE(entity->GetComponent<MockComponent1>() != nullptr);
            }

            for (auto* entity : entitiesWithMock1)
            {
                entity->RemoveComponent<MockComponent1>();

                // Check that entity don't have mock1 or mock2
                REQUIRE_FALSE(entity->GetComponent<MockComponent1>() != nullptr);
                REQUIRE_FALSE(entity->GetComponent<MockComponent2>() != nullptr);
            }
        }

        SECTION("Component management")
        {
            for (auto& entity : entitiesWithMock1)
            {
                entity->AddComponent<MockComponent1>();
                REQUIRE(entity->GetComponent<MockComponent1>() != nullptr);

                entity->RemoveComponent<MockComponent1>();
                REQUIRE_FALSE(entity->GetComponent<MockComponent1>() != nullptr);

                entity->AddComponent<MockComponent1>();
                REQUIRE(entity->GetComponent<MockComponent1>() != nullptr);
            }
        }
    }

    SECTION("Check component validity")
    {
        red::World world;
        world.Init();

        world.RegisterComponentType<MockComponent1>();
        world.RegisterComponentType<MockComponent11>();
        world.RegisterComponentType<MockComponent2>();

        auto* entityA = world.CreateWorldEntity("a");
        REQUIRE(entityA != nullptr);

        auto* componentAddedA = entityA->AddComponent<MockComponent1>();
        REQUIRE(componentAddedA != nullptr);

        auto* entityB = world.CreateWorldEntity("b");
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

namespace EntityDestroyRemoveComp
{
class TestSystem : public red::System<red::QueryGroup<red::QueryRO<MockComponent1>>>
{
public:
    explicit TestSystem(red::World* world) : red::System<red::QueryGroup<red::QueryRO<MockComponent1>>>(world)
    {
    }
    virtual ~TestSystem() = default;

    void Update() override
    {
        auto result = QueryComponents<0>();

        m_entityCount = result.size();
    }

    int m_entityCount = 0;
};
}  // namespace EntityDestroyRemoveComp

TEST_CASE("Entity destroy remove components", "[ECS]")
{
    using namespace red;
    using namespace EntityDestroyRemoveComp;

    red::CreateEngineFrom<EngineTest>(0, nullptr);  // For double allocator

    red::World world;
    world.Init();

    world.RegisterComponentType<MockComponent1>();
    auto* testSystem = world.AddSystem<TestSystem>();

    auto* entityA = world.CreateWorldEntity("a");
    entityA->AddComponent<MockComponent1>();

    world.Update();

    REQUIRE(testSystem->m_entityCount == 1);

    entityA->Destroy();
    world.Update();

    REQUIRE(testSystem->m_entityCount == 0);
}