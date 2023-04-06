#include "SystemTest.hpp"

#include "RedEngine/Core/Entity/SystemExecutionGraph.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Thread/ExecutionGraph.hpp"

#include <catch2/catch.hpp>
#include <iostream>

#include "EngineTest.hpp"
#include "TestModule.hpp"

TEST_CASE("System", "[ECS]")
{
    auto* engine = CreateEngineFrom<EngineTest>(0, nullptr);  // For double allocator

    red::World world;
    world.Init();
    world.RegisterComponentType<red::EventsComponent>();
    world.RegisterComponentType<MockComponent1>();
    world.RegisterComponentType<MockComponent2>();

    auto* e = world.CreateWorldEntity("a");
    e->AddComponent<red::EventsComponent>();

    size_t baseSystemCount = world.GetSystems().size();
    auto* mockSystemPtr = world.AddSystem<MockSystem>();

    ExecutionGraph graph;
    graph.AddStage(SystemGraphStageBuilder::NewStage(&world).AddSystem<MockSystem>().Build());
    world.SetExecutionGraph(std::move(graph));

    SECTION("Adding mock system")
    {
        REQUIRE(world.GetSystems().size() == (baseSystemCount + 1));
        REQUIRE(mockSystemPtr != nullptr);
    }

    SECTION("Update world update Systems")
    {
        world.Update();

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
    }

    SECTION("System is fetching the right entities")
    {
        auto* e1 = world.CreateWorldEntity("e1");
        auto* e2 = world.CreateWorldEntity("e2");
        auto* e3 = world.CreateWorldEntity("e3");

        e1->AddComponent<MockComponent1>();
        e2->AddComponent<MockComponent1>();

        e2->AddComponent<MockComponent2>();
        e3->AddComponent<MockComponent2>();

        world.Update();

        REQUIRE(mockSystemPtr->m_hasBeenUpdated);
        REQUIRE(mockSystemPtr->m_entityCount == 1);  // only e2 has the right components types
    }

    engine->Destroy();
}

TEST_CASE("System RO/RW introspection", "[ECS]")
{
    using namespace red;

    struct TestSystem : public System<QueryGroup<QueryRO<MockComponent1>>, QueryGroup<QueryRW<MockComponent2>>,
                                      SinglQuery<QueryRW<MockComponent11>>>
    {
        TestSystem(World* world) : System(world)
        {
        }

        void Update() override
        {
        }
    };

    auto* engine = CreateEngineFrom<EngineTest>(0, nullptr);  // For double allocator

    red::World world;
    world.Init();
    world.RegisterComponentType<MockComponent1>();
    world.RegisterComponentType<MockComponent2>();
    world.RegisterComponentType<MockComponent11>();

    auto* testSystemPtr = world.AddSystem<TestSystem>();

    auto roComponents = testSystemPtr->GetROComponents();
    auto rwComponents = testSystemPtr->GetRWComponents();

    REQUIRE(std::find_if(roComponents.begin(), roComponents.end(),
                         [](const TypeTraits& type)
                         { return type.typeId == TypeInfo<MockComponent1>().typeId; }) != roComponents.end());

    REQUIRE(std::find_if(rwComponents.begin(), rwComponents.end(),
                         [](const TypeTraits& type)
                         { return type.typeId == TypeInfo<MockComponent2>().typeId; }) != rwComponents.end());

    REQUIRE(std::find_if(rwComponents.begin(), rwComponents.end(),
                         [](const TypeTraits& type)
                         { return type.typeId == TypeInfo<MockComponent11>().typeId; }) != rwComponents.end());

    engine->Destroy();
}