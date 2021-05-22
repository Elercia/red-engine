#include "PongEngine.hpp"
#include "PongLevel.hpp"

#include "RedEngine/Core/Engine.hpp"

using namespace red;
using namespace pong;

int main(int argc, char* argv[])
{
    auto* engine = CreateEngineFrom<PongEngine>(argc, argv);

    return engine->MainLoop();
}
