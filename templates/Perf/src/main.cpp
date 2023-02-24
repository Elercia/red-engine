#include "PerfEngine.hpp"
#include "PerfLevel.hpp"

#include "RedEngine/Core/Engine.hpp"

using namespace red;
using namespace perf;

int main(int argc, char* argv[])
{
    auto* engine = CreateEngineFrom<PerfEngine>(argc, argv);

    engine->MainLoop();

    engine->Destroy();

    return EXIT_SUCCESS;
}
