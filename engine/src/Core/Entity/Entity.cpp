#include "RedEngine/Core/Entity/Entity.hpp"

namespace red
{
Entity::Entity(World* world, EntityId_t id) : m_world(world), m_id(id) {}

void Entity::Destroy()
{
    // TODO For future : call the free of this part of the memory
}

std::set<Component*> Entity::GetComponents()
{
    return m_world->GetComponentManager()->GetComponents(this);
}

EntityId_t Entity::GetId() const { return m_id; }

}  // namespace red
