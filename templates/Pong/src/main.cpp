#include "PongEngine.hpp"
#include "PongLevel.hpp"

#include "RedEngine/Core/Engine.hpp"

using namespace red;
using namespace pong;

int main(int argc, char* argv[])
{
    auto* engine = CreateEngineFrom<PongEngine>(argc, argv);

    bool mainLoopError = engine->MainLoop();

    engine->Destroy();

    return mainLoopError ? EXIT_SUCCESS : EXIT_FAILURE;
}
