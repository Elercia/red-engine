#include "RedEngine/Level/LevelChunk.hpp"

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Level/Level.hpp"

namespace red
{
LevelChunk::LevelChunk(Level* owner) : m_level(owner), m_world(owner->GetWorld())
{
    m_rootEntity = new Entity(m_world, m_world->GetNewEntityId());
}

LevelChunk::LevelChunk(World* owner) : m_level(nullptr), m_world(owner)
{
    m_rootEntity = new Entity(m_world, m_world->GetNewEntityId());
}

LevelChunk::~LevelChunk()
{
    delete m_rootEntity;
}

Array<Entity*>& LevelChunk::GetEntities()
{
    return m_ownedEntities;
}

const Array<Entity*>& LevelChunk::GetEntities() const
{
    return m_ownedEntities;
}

Entity* LevelChunk::GetRootEntity()
{
    return m_rootEntity;
}

const Entity* LevelChunk::GetRootEntity() const
{
    return m_rootEntity;
}

void LevelChunk::Init()
{
    m_world->OnAddEntities(m_ownedEntities);
}

void LevelChunk::Finalize()
{
    m_world->OnRemoveEntities(m_ownedEntities);

    for (auto* e : m_ownedEntities)
    {
        e->Destroy();
    }
}

void LevelChunk::Clean()
{
    std::vector<Entity*> entitiesToRemove;
    for (auto* entity : m_ownedEntities)
    {
        if (entity->GetState() == EntityState::Destroyed)
        {
            m_world->AddGarbageEntityId(entity->GetId());
            entity->SetParent(nullptr);

            entitiesToRemove.push_back(entity);
        }
    }
    
    for (auto* e : entitiesToRemove)
    {
        m_ownedEntities.erase(std::remove(m_ownedEntities.begin(), m_ownedEntities.end(), e), m_ownedEntities.end());
        delete e;
    }

    m_world->OnRemoveEntities(entitiesToRemove);
}

Entity* LevelChunk::CreateEntity()
{
    auto* e = CreateEntity(m_world->GetNewEntityId());
    return e;
}

Entity* LevelChunk::CreateEntity(EntityId entityId, Entity* parent)
{
    auto* e = CreateEntity(entityId);

    e->SetParent(parent);

    return e;
}

Entity* LevelChunk::CreateEntity(EntityId entityId, const std::string& name)
{
    auto* e = CreateEntity(entityId);

    e->SetName(name);

    return e;
}

Entity* LevelChunk::CreateEntity(EntityId entityId, const std::string& name, Entity* parent)
{
    auto* e = CreateEntity(entityId, name);

    e->SetParent(parent);

    return e;
}

Entity* LevelChunk::CreateEntity(const std::string& name)
{
    auto* e = CreateEntity();

    e->SetName(name);

    return e;
}

Entity* LevelChunk::CreateEntity(const std::string& name, Entity* parent)
{
    auto* e = CreateEntity(name);

    e->SetParent(parent);

    return e;
}

Entity* LevelChunk::CreateEntity(EntityId entityId)
{
    auto* entityPtr = new Entity(m_world, entityId);
    entityPtr->SetParent(m_rootEntity);

    m_ownedEntities.push_back(entityPtr);

    return entityPtr;
}

}  // namespace red
