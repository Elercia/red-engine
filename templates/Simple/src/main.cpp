#include <RedEngine/Application.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Core/Configuration/Configuration.hpp>
#include <RedEngine/Rendering/Components/Sprite.hpp>

int main(int argc, char* argv[])
{
    red::Configuration::GetInstance().LoadConfigFile("resources/config.ini");
    red::Configuration::GetInstance().ParseCommandLine(argc, argv);

    red::Application app;

    auto& world = app.CreateWorld();
    auto* ent = world.CreateEntity();
    ent->AddComponent<red::Sprite>("resources/pacman.bmp");

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
