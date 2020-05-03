#include <RedEngine/Application/Application.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include "DefaultLevel.hpp"

int main(int argc, char* argv[])
{
    red::Configuration::LoadConfigFile("resources/config.ini");
    red::GetRedSubEngine<red::Configuration>()->ParseCommandLine(argc, argv);

    red::Engine::Init();

    red::Application app;

    app.LoadLevel<DefaultLevel>();

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
