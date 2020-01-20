#include <RedEngine/ecs/Entity.hpp>

namespace red
{
Entity::Entity(World* world, EntityId_t id) : m_world(world), m_id(id)
{}

void Entity::Destroy()
{
    // TODO For future : call the free of this part of the memory
}

std::set<std::shared_ptr<Component>>& Entity::GetComponents()
{
    return m_components;
}

EntityId_t Entity::GetId() const
{
    return m_id;
}

} // namespace red
