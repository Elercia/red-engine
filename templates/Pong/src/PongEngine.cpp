#include "PongEngine.hpp"

#include "PongLevel.hpp"

namespace pong
{
bool PongEngine::Create()
{
    m_world->LoadLevel<PongLevel>();

    return true;
}

bool PongEngine::Destroy()
{
    return true;
}

std::string_view PongEngine::GetGameName() const
{
    return "Pong Template";
}
}  // namespace pong
