#include "RedEngine/Core/Entity/Components/Component.hpp"

namespace red
{
Component::Component(Entity* entity) : m_owner(entity), m_status()
{
}

Entity* Component::GetOwner() const
{
    return m_owner;
}

void Component::Serialize(ILevelComponentData* /*levelComponentData*/) const
{
}

void Component::Deserialize(const ILevelComponentData* /*levelComponentData*/)
{
}

}  // namespace red
