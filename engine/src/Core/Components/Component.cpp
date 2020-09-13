#include "RedEngine/Core/Components/Component.hpp"

namespace red
{
Component::Component(Entity* entity) : m_componentId(0), m_owner(entity), m_status() {}

ComponentId_t Component::GetComponentId() const { return m_componentId; }

Entity* Component::GetOwner() const { return m_owner; }

}  // namespace red
