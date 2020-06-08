#include "RedEngine/Core/Entity/World.hpp"

#include <algorithm>
#include <cassert>

#include "RedEngine/Core/Components/ComponentManager.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Debug/Debug.hpp"

namespace red
{
World::World()
    : m_singletonEntity(nullptr)
    , m_componentManager(new ComponentManager())
    , m_nextEntityId(MaxPersistentEntities)
    , m_nextPersistentEntityId(0)
{
}

World::~World()
{
    for (auto& system : m_systems)
    {
        system->Finalise();
        delete system;
    }

    for (auto& entity : m_entities)
    {
        DestroyEntity(entity);
    }

    delete m_componentManager;
}

Entity* World::CreateEntity() { return CreateEntity(""); }

Entity* World::CreateEntity(const std::string& name)
{
    auto entityPtr = new Entity(this, m_nextEntityId++, name);

    m_entities.push_back(entityPtr);

    return entityPtr;
}

red::Entity* World::CreateSingletonEntity()
{
    m_singletonEntity = new Entity(this, m_nextEntityId++, "__SingletonEntity__");
    m_singletonEntity->SetPersistent(true);

    return m_singletonEntity;
}

void World::Init()
{
    for (auto& system : m_systems)
    {
        system->Init();
    }
}

void World::Update()
{
    for (auto& system : m_systems)
    {
        system->PreUpdate();
    }

    for (auto& system : m_systems)
    {
        system->Update();
    }

    for (auto& system : m_systems)
    {
        system->LateUpdate();
    }
}

const std::vector<System*>& World::GetSystems() { return m_systems; }

const std::vector<Entity*>& World::GetEntities() { return m_entities; }

Entity& World::GetSingletonEntity() { return *m_singletonEntity; }

ComponentManager* World::GetComponentManager() { return m_componentManager; }

void World::DestroyEntity(Entity* entity) { delete entity; }

void World::SetEntityPersistency(Entity* entity, bool persistent)
{
    EntityId_t entityId;
    if (persistent)
    {
        if (m_nextPersistentEntityId + 1 >= MaxPersistentEntities)
            RED_ABORT("Cant set the entity persistence because we've reached the limit");

        entityId = m_nextPersistentEntityId;
        m_nextPersistentEntityId++;
    }
    else
    {
        entityId = m_nextEntityId;
        m_nextEntityId++;
    }

    auto oldEntityId = entity->GetId();
    entity->SetId(entityId);
    m_componentManager->MoveComponents(oldEntityId, entityId);
}

void World::UnloadTransientEntities()
{
    m_componentManager->UnloadTransientComponents();

    m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                    [](Entity* e) { return e->GetId() >= MaxPersistentEntities; }),
                     m_entities.end());
}

void World::UnloadSystems()
{
    for (auto& system : m_systems)
    {
        system->Finalise();
    }

    m_systems.clear();
}

}  // namespace red
