#include "RedEngine/Core/Entity/System.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"

namespace red
{
System::System(World* world) : m_world(world) {}

Entity* System::GetSingletonEntity() { return m_world->GetSingletonEntity(); }

void System::DebugDrawLine(const Vector2& from, const Vector2& to)
{
    auto* debugComp = GetSingletonEntity()->GetComponent<DebugComponent>();

    debugComp->AddLine(from, to);
}

}  // namespace red
