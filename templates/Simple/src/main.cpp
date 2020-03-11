#include <RedEngine/Application.hpp>
#include <RedEngine/components/RigidBody.hpp>
#include <RedEngine/ecs/Entity.hpp>

#include "CustomComponent.hpp"

int main(int argc, char* argv[])
{
    red::Application app;

    app.InitFromCommandLine(argc, argv);

    std::string title = "Template Simple";

    auto world = app.CreateWorld();
    auto window = app.InitWindow(title);

    auto entity = world->CreateEntity();
    entity->AddComponent<CustomComponent>();
    entity->AddComponent<red::RigidBody>();

    app.Run();

    return EXIT_SUCCESS;
}
