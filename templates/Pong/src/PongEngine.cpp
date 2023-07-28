#include "PongEngine.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"

#include "PongLevel.hpp"
#include "ScoreComponent.hpp"

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

StringView PongEngine::GetGameName() const
{
    return "Pong Template";
}

bool PongEngine::RegisterComponentTypes()
{
    CheckReturn(Engine::RegisterComponentTypes());

    m_world->RegisterComponentType<ScoreComponent>();

    return true;
}

}  // namespace pong
