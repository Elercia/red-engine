#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#include "RedEngine/Core/Engine.hpp"

int main(int argc, char* argv[])
{
    // global setup...
    red::EngineInitDesc desc;
    desc.config.resourceFolder = "resources";
    desc.config.argc = argc;
    desc.config.argv = argv;
    red::Engine::Init(desc);

    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}