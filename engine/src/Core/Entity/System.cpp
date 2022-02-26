#include "RedEngine/Core/Entity/System.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
System::System(World* world) : m_isInit(false), m_world(world), m_priority(0), m_typeTraits(EmptyTypeTraits)
{
}

void System::DebugDrawLine(const Vector2& from, const Vector2& to)
{
    auto* debugComp = m_world->GetWorldComponent<DebugComponent>();

    debugComp->AddLine(from, to);
}

void System::SetTypeTraits(TypeTraits typeTraits)
{
    m_typeTraits = typeTraits;
}

std::size_t System::GetTypeId() const
{
    return m_typeTraits.typeId;
}

int System::GetPriority() const
{
    return m_priority;
}

Array<Entity*>& System::GetWorldEntities()
{
    return m_world->GetEntities();
}

const Array<Entity*>& System::GetWorldEntities() const
{
    return m_world->GetEntities();
}

void System::Init()
{
    m_isInit = true;

    RED_LOG_INFO("Init {} system", m_typeTraits.name);
}

void System::Finalise()
{
    m_isInit = false;
}

}  // namespace red
