#include "RedEngine/Core/Entity/Components/Component.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
Component::Component(Entity* entity) : m_owner(entity), m_status()
{
}

Entity* Component::GetOwner() const
{
    return m_owner;
}

TypeTraits Component::GetTypeTraits() const
{
    return m_typeTraits;
}

World* Component::GetWorld() const
{
    return m_owner->GetWorld();
}

}  // namespace red
