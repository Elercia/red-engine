#include "RedEngine/Core/Components/Component.hpp"

namespace red
{
Component::Component(Entity* entity) : m_owner(entity), m_status() {}

Entity* Component::GetOwner() const { return m_owner; }

}  // namespace red
