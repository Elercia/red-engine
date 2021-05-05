#define CATCH_CONFIG_RUNNER
#include "catch2/catch.hpp"

#include "RedEngine/Core/Engine.hpp"

int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);

    // global clean-up...

    return result;
}