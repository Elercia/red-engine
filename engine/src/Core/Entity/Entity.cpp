#include "RedEngine/Core/Entity/Entity.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"

#include <utility>

namespace red
{
Entity::Entity(World* world, EntityId id) : m_world(world), m_id(id)
{
    m_transform = AddComponent<Transform>(0.F, 0.F);
}

void Entity::Destroy()
{
    // Destroyed entities will be removed on the next World Update iteration
    m_state = EntityState::Destroyed;

    for (auto* child : m_children)
    {
        child->Destroy();
    }
}

Component* Entity::AddComponent(const std::string& name)
{
    auto* componentManager = GetComponentManager();

    auto inferedTraits = GetTypeInfoFromTypeName(name);

    if (auto* comp = componentManager->GetComponent(this, inferedTraits); comp != nullptr)
    {
        RED_LOG_WARNING("Entity {} already has the component {}", m_name, name);
        return comp;
    }

    auto componentPtr = componentManager->CreateComponentFromName(this, inferedTraits);

    return componentPtr;
}

Array<Component*> Entity::GetComponents() const
{
    return m_world->GetComponentManager()->GetComponents(this);
}

EntityId Entity::GetId() const
{
    return m_id;
}

void Entity::SetId(EntityId id)
{
    m_id = id;
}

const std::string& Entity::GetName() const
{
    return m_name;
}

void Entity::SetName(const std::string& name)
{
    m_name = name;
}

EntityState Entity::GetState() const
{
    return m_state;
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
    }
}

void Entity::AddChild(Entity* child)
{
    m_children.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);

    if (it == m_children.end())
    {
        RED_LOG_WARNING("Entity RemoveChild child is not part of children (parent {}, child {})", m_name,
                        child->m_name);
        return;
    }

    m_children.erase(it);
}

Entity* Entity::GetParent()
{
    return m_parent;
}

const Entity* Entity::GetParent() const
{
    return m_parent;
}

const Array<Entity*>& Entity::GetChildren() const
{
    return m_children;
}

World* Entity::GetWorld()
{
    return m_world;
}

ComponentManager* Entity::GetComponentManager()
{
    return m_world->GetComponentManager();
}

}  // namespace red
