#include <RedEngine/debug/Debug.hpp>
#include <RedEngine/ecs/ComponentManager.hpp>
#include <RedEngine/ecs/Entity.hpp>
#include <RedEngine/ecs/World.hpp>
#include <algorithm>
#include <cassert>

namespace red
{

std::vector<std::shared_ptr<System>>& World::GetSystems()
{
    return m_systems;
}

World::World() : m_componentManager(new ComponentManager()), m_nextEntityId(0)
{}

World::~World()
{
    for (auto& entity : m_entities)
    {
        entity->Destroy();
    }

    delete m_componentManager;
}

std::shared_ptr<Entity> World::CreateEntity()
{
    auto entityPtr = std::make_shared<Entity>(this, m_nextEntityId++);

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

ComponentManager* World::GetComponentManager()
{
    return m_componentManager;
}
} // namespace red
