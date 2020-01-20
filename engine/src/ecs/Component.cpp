#include <RedEngine/ecs/Component.hpp>

namespace red
{
Component::Component(Entity* entity) : m_componentId(0), m_owner(entity)
{}

ComponentName_t Component::GetComponentId() const
{
    return m_componentId;
}

Entity* Component::GetOwner() const
{
    return m_owner;
}
} // namespace red
