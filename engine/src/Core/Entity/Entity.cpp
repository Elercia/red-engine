#include <RedEngine/Debug/Logger/Logger.hpp>
#include <utility>
#include "RedEngine/Core/Entity/Entity.hpp"

namespace red
{
Entity::Entity(World* world, EntityId_t id, std::string name)
    : m_world(world), m_id(id), m_name(std::move(name)), m_parent(nullptr), m_isPersistent(false)
{
}

void Entity::Destroy()
{
    // TODO For future : call the free of this part of the memory
}

std::set<Component*> Entity::GetComponents()
{
    return m_world->GetComponentManager()->GetComponents(this);
}

EntityId_t Entity::GetId() const { return m_id; }
void Entity::SetId(EntityId_t id) { m_id = id; }

void Entity::SetPersistent(bool persistent)
{
    if (m_isPersistent != persistent)
    {
        if (m_parent != nullptr && m_parent->m_isPersistent != persistent)
        {
            m_parent->SetPersistent(persistent);
            return;
        }

        m_isPersistent = persistent;

        m_world->SetEntityPersistency(this, persistent);

        for (auto& child : m_children)
        {
            child->SetPersistent(persistent);
        }
    }
}

void Entity::SetParent(Entity* parent)
{
    // Unset the entity parent
    if (m_parent != nullptr)
    {
        m_parent->RemoveChild(this);
        m_parent = nullptr;
    }

    // if we want to set a new parent
    if (parent != nullptr)
    {
        // Set the parent of this entity
        m_parent = parent;
        m_parent->AddChild(this);

        SetPersistent(m_parent->m_isPersistent);
    }
}

void Entity::AddChild(Entity* child) { m_children.push_back(child); }

void Entity::RemoveChild(Entity* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);

    if (it == m_children.end())
    {
        RED_LOG_WARNING("Entity RemoveChild child is not part of children (parent {}, child {})",
                        m_name, child->m_name);
    }

    m_children.erase(it);
}

}  // namespace red
