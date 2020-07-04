#include <RedEngine/Core/Application.hpp>
#include <RedEngine/Core/Entity/World.hpp>
#include <RedEngine/Core/Entity/Entity.hpp>
#include "PongLevel.hpp"

int main(int argc, char* argv[])
{
    red::EngineInitDesc desc;
    desc.config.resourceFolder = "resources";
    desc.config.argc = argc;
    desc.config.argv = argv;
    red::Engine::Init(desc);

    red::Application&  app = red::GetRedInstance().GetApplication();

    app.LoadLevel<PongLevel>();

    return app.Run() ? EXIT_SUCCESS : EXIT_FAILURE;
}
