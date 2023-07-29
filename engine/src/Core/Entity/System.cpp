#include "RedEngine/Core/Entity/System.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
BaseSystem::BaseSystem(World* world) : Uncopyable(), m_world(world), m_typeTraits(EmptyTypeTraits)
{
}

TypeTraits BaseSystem::GetTypeTraits() const
{
    return m_typeTraits;
}

Array<Entity*>& BaseSystem::GetEntities()
{
    return m_world->GetEntities();
}

void BaseSystem::SetTraits(TypeTraits typeTraits)
{
    m_typeTraits = typeTraits;
}

}  // namespace red
