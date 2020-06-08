#include <RedEngine/Application/Application.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include "DefaultLevel.hpp"

int main(int argc, char* argv[])
{
    red::Engine::Init("resources", argc, argv);

    red::Application app;

    app.LoadLevel<DefaultLevel>();

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
