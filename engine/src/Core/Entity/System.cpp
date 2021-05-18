#include "RedEngine/Core/Entity/System.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
System::System(World* world) : m_isInit(false), m_world(world), m_priority(0), m_typeId(0)
{
}

Entity* System::GetSingletonEntity()
{
    return m_world->GetSingletonEntity();
}

void System::DebugDrawLine(const Vector2& from, const Vector2& to)
{
    auto* debugComp = GetSingletonEntity()->GetComponent<DebugComponent>();

    debugComp->AddLine(from, to);
}

void System::SetTypeId(std::size_t typeId)
{
    m_typeId = typeId;
}

std::size_t System::GetTypeId()
{
    return m_typeId;
}

int System::GetPriority() const
{
    return m_priority;
}

std::vector<Entity*> System::GetWorldEntities()
{
    return m_world->GetEntities();
}

}  // namespace red
