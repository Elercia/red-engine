#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Physics/Components/PhysicBody.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"

#include <catch2/catch.hpp>

#include "EngineTest.hpp"
#include "TestModule.hpp"

int size(b2Fixture* fixture)
{
    int nb = 0;

    while (fixture != nullptr)
    {
        nb++;
        fixture = fixture->GetNext();
    }
    return nb;
}

TEST_CASE("Component binding", "[PHYSICS]")
{
    using namespace red;

    auto engine = CreateEngineFrom<EngineTest>(0, nullptr);  // For double allocator

    World w;
    w.Init();
    w.RegisterComponentType<PhysicBody>();

    Entity* e = w.CreateWorldEntity("a");
    PhysicSystem* system = w.AddSystem<PhysicSystem>();

    red::PhysicBodyCreationDesc desc = {red::PhysicsBodyType::DYNAMIC_BODY};

    auto* body = e->AddComponent<PhysicBody>(desc);

    {
        red::CircleColliderDesc circleColliderDesc;
        circleColliderDesc.isTrigger = false;
        circleColliderDesc.center = {5.F, 5.F};
        circleColliderDesc.radius = 5.F;
        circleColliderDesc.restitution = 1.f;
        circleColliderDesc.friction = 0.f;

        body->AddCircleCollider(circleColliderDesc);
    }

    {
        red::PolygonColliderDesc polygonColliderDesc;
        polygonColliderDesc.isTrigger = false;
        polygonColliderDesc.points = {{0, 0}, {30, 0}, {30, 100}, {0, 100}};
        polygonColliderDesc.restitution = 1.f;

        body->AddPolygonCollider(polygonColliderDesc);
    }

    {
        red::EdgeColliderDesc edgeColliderDesc;
        edgeColliderDesc.isTrigger = false;
        edgeColliderDesc.start = {0.f, 0.f};
        edgeColliderDesc.end = {1.f, 0.f};

        body->AddEdgeCollider(edgeColliderDesc);
    }

    system->Init();

    REQUIRE(size(body->GetBody()->GetFixtureList()) == 3);

    system->Finalize();

    engine->Destroy();
}
