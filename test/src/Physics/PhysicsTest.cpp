#include <RedEngine/Core/Entity/Entity.hpp>

#include <RedEngine/Physics/Components/Collider.hpp>
#include <RedEngine/Physics/Components/PhysicBody.hpp>

#include <catch2/catch.hpp>

int size(b2Fixture* fixture)
{
    int nb = 0;

    while (fixture)
    {
        nb++;
        fixture = fixture->GetNext();
    }
    return nb;
}

TEST_CASE("Component binding", "[PHYSICS]")
{
    using namespace red;
    World w;
    Entity* e = w.CreateEntity();

    auto* body = e->AddComponent<PhysicBody>();
    auto* list = e->AddComponent<ColliderList>();

    list->AddCircleCollider({false, {0, 0}, 10.F});
    list->AddEdgeCollider({false, {0, 0}, {0, 0}});
    list->AddPolygonCollider({false,
                              {
                                  {0, 0},
                                  {1, 1},
                                  {2, 1},
                                  {3, 4},
                                  {4, 3},

                              }});

    REQUIRE(size(body->GetBody()->GetFixtureList()) == 3);
}