#include "RedEngine/Core/Entity/World.hpp"

#include <algorithm>
#include <cassert>

#include "RedEngine/Core/Components/ComponentManager.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Debug/Debug.hpp"

namespace red
{
World::World() : m_componentManager(new ComponentManager()), m_nextEntityId(0) {}

World::~World()
{
    for (auto& entity : m_entities)
    {
        DestroyEntity(entity);
    }

    delete m_componentManager;
}

Entity* World::CreateEntity()
{
    auto entityPtr = new Entity(this, m_nextEntityId++);

    m_entities.push_back(entityPtr);

    return entityPtr;
}

void World::Update(float deltaTime)
{
    for (auto& system : m_systems)
    {
        system->Update(deltaTime);
    }
}

const std::vector<System*>& World::GetSystems() { return m_systems; }

const std::vector<Entity*>& World::GetEntities() { return m_entities; }

ComponentManager* World::GetComponentManager() { return m_componentManager; }

void World::DestroyEntity(Entity* entity) {}
}  // namespace red
