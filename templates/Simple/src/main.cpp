#include <RedEngine/Application/Application.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include <RedEngine/Core/Configuration/Configuration.hpp>
#include <RedEngine/Rendering/Components/Sprite.hpp>
#include "DefaultLevel.hpp"
#include <RedEngine/Core/Components/Sprite.hpp>
#include <RedEngine/Resources/ResourceEngine.hpp>

int main(int argc, char* argv[])
{
    red::Engine::Init();

    red::Configuration::GetInstance().LoadConfigFile("resources/config.ini");
    red::Configuration::GetInstance().ParseCommandLine(argc, argv);

    red::Application app;

    //    auto& world = app.CreateWorld();
    //    auto* ent = world.CreateEntity();
    //    ent->AddComponent<red::Sprite>("resources/pacman.bmp");

    app.LoadLevel<DefaultLevel>();
    auto& famtomTexture = red::ResourceEngine::LoadTexture("resources/fantom.bmp");
    auto& pacManTexture = red::ResourceEngine::LoadTexture("resources/pacman.bmp");

    auto& world = app.CreateWorld();
    auto* fantom1 = world.CreateEntity();
    auto* fantom2 = world.CreateEntity();

    fantom1->AddComponent<red::Transform>(100, 20);
    fantom1->AddComponent<red::Sprite>(famtomTexture);

    fantom2->AddComponent<red::Transform>(300, 100);
    fantom2->AddComponent<red::Sprite>(famtomTexture);

    auto* pacman = world.CreateEntity();
    pacman->AddComponent<red::Transform>(200, 10);
    pacman->AddComponent<red::Sprite>(pacManTexture);

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
