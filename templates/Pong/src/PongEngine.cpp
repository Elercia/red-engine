#include "PongEngine.hpp"

#include "PongLevel.hpp"

namespace pong
{
bool PongEngine::Create()
{
    bool init = Engine::Create();

    if (init)
    {
        m_world->LoadLevel<PongLevel>();
    }

    return init;
}

std::string_view PongEngine::GetGameName() const
{
    return "Pong Template";
}

}  // namespace pong
