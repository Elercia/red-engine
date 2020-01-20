#include "CustomComponent.hpp"

#include <RedEngine/Application.hpp>
#include <RedEngine/components/RigidBody.hpp>
#include <RedEngine/ecs/Entity.hpp>
#include <RedEngine/ecs/World.hpp>

int main(int argc, char* argv[])
{
    red::Application app(argc, argv);

    auto world = app.CreateWorld();
    auto window = app.CreateWindow();

    auto entity = world->CreateEntity();
    entity->AddComponent<CustomComponent>();
    entity->AddComponent<red::RigidBody>();

    app.Run();

    return EXIT_SUCCESS;
}
