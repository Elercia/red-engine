#include "PongEngine.hpp"

#include "PongLevel.hpp"

namespace pong
{
bool PongEngine::Create()
{
    CheckReturn(Engine::Create());

    m_world->LoadLevel<PongLevel>();

    return true;
}

bool PongEngine::Destroy()
{
    CheckReturn(Engine::Destroy());

    return true;
}

std::string_view PongEngine::GetGameName() const
{
    return "Pong Template";
}
}  // namespace pong
