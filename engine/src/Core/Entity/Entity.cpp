#include "RedEngine/Core/Entity/Entity.hpp"

#include "RedEngine/Core/Debug/Logger/Logger.hpp"
#include "RedEngine/Core/Engine.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Level/LevelData.hpp"

#include <utility>

namespace red
{
Entity::Entity(World* world, EntityId id, std::string name)
    : m_world(world), m_id(id), m_name(std::move(name)), m_isPersistent(false), m_parent(nullptr)
{
    AddComponent<Transform>(0.F, 0.F);
}

void Entity::Destroy()
{
    for (auto* child : m_children)
    {
        child->Destroy();
    }

    // TODO Check if the component are really destroyed

    m_isDestroyed = true;
}

Array<Component*> Entity::GetComponents() const
{
    return m_world->GetComponentManager()->GetComponents(this);
}

EntityId Entity::GetId() const
{
    return m_id;
}

bool Entity::IsRootEntity() const
{
    return m_parent == nullptr;
}

void Entity::SetId(EntityId id)
{
    m_id = id;
}

const std::string& Entity::GetName() const
{
    return m_name;
}

void Entity::SetPersistent(bool persistent)
{
    // Do we need to change the persitency
    if (m_isPersistent != persistent)
    {
        // A child cant have a persitency different it parent
        if (m_parent != nullptr && !m_parent->IsRootEntity() && m_parent->m_isPersistent != persistent)
        {
            m_parent->SetPersistent(persistent);
            return;
        }

        // Set the parent persitency and the childs ones
        m_isPersistent = persistent;

        for (auto& child : m_children)
        {
            child->SetPersistent(persistent);
        }

        // Only change the parent of the top parent entity (to keep the child heritage)
        if (m_parent == nullptr || m_parent->IsRootEntity())
        {
            if (m_isPersistent)
            {
                SetParent(m_world->GetSingletonEntity());
            }
            else
            {
                SetParent(nullptr);
            }
        }

        // Change the parent of the current entity to be the singletonEntity
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

        if (!m_parent->IsRootEntity())
            SetPersistent(m_parent->m_isPersistent);
    }

    m_isDirty = true;
}

void Entity::AddChild(Entity* child)
{
    m_children.push_back(child);
    m_isDirty = true;
}

void Entity::RemoveChild(Entity* child)
{
    auto it = std::find(m_children.begin(), m_children.end(), child);

    if (it == m_children.end())
    {
        RED_LOG_WARNING("Entity RemoveChild child is not part of children (parent {}, child {})", m_name,
                        child->m_name);
    }

    m_children.erase(it);

    m_isDirty = true;
}

Entity* Entity::GetParent()
{
    return m_parent;
}

std::vector<Entity*> Entity::GetChildren() const
{
    return m_children;
}

World* Entity::GetWorld()
{
    return m_world;
}

red::ComponentManager* Entity::GetComponentManager()
{
    return m_world->GetComponentManager();
}

void Entity::Serialize(ILevelEntityData* entityData) const
{
    for (auto* child : GetChildren())
    {
        child->Serialize(entityData->AddLevelChildEntityData());
    }

    entityData->SetId(m_id);
    entityData->SetName(m_name);

    if (m_parent != nullptr)
        entityData->SetParentId(m_parent->GetId());

    for (auto* comp : GetComponents())
    {
        comp->Serialize(entityData->AddLevelComponentData(std::string(comp->GetComponentName())));
    }
}

void Entity::Deserialize(const ILevelEntityData* /*entity*/)
{
}

}  // namespace red
