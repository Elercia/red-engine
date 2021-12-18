#include "PongEngine.hpp"

#include "PongLevel.hpp"

namespace pong
{
bool PongEngine::Create()
{
    CheckReturn(Engine::Create(), false);

    m_world->LoadLevel<PongLevel>();

    return true;
}

bool PongEngine::Destroy()
{
    CheckReturn(Engine::Destroy(), false);

    return true;
}

std::string_view PongEngine::GetGameName() const
{
    return "Pong Template";
}
}  // namespace pong
