#include "PerfEngine.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"

#include "PerfLevel.hpp"

namespace perf
{
bool PerfEngine::Create()
{
    CheckReturn(Engine::Create());

    m_world->LoadLevel<PerfLevel>();

    return true;
}

bool PerfEngine::Destroy()
{
    CheckReturn(Engine::Destroy());

    return true;
}

StringView PerfEngine::GetGameName() const
{
    return "Perf Template";
}

}  // namespace Perf
