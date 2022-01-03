#include "RedEngine/Core/Entity/Components/Component.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/World.hpp"

namespace red
{
RED_COMPONENT_BASIC_FUNCTIONS_IMPL(Component);

Component::Component(Entity* entity) : m_owner(entity), m_status()
{
}

Entity* Component::GetOwner() const
{
    return m_owner;
}

World* Component::GetWorld() const
{
    return m_owner->GetWorld();
}

}  // namespace red
