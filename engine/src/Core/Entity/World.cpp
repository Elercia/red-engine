#include "RedEngine/Core/Entity/World.hpp"

#include "RedEngine/Core/Components/ComponentManager.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/Level.hpp"

#include <algorithm>
#include <cassert>

namespace red
{
World::World()
    : m_singletonEntity(nullptr), m_componentManager(new ComponentManager()), m_nextEntityId(0), m_physicsWorld()
{
}

World::~World()
{
    for (auto& system : m_systems)
    {
        system->Finalise();
    }

    for (auto& system : m_systems)
    {
        delete system;
    }

    for (auto& entity : m_entities)
    {
        entity->Destroy();
    }

    for (auto& entity : m_entities)
    {
        delete entity;
    }

    delete m_componentManager;
}

red::Entity* World::CreateRootEntity(Level* level)
{
    auto* entityPtr = CreateEntity("root_" + level->GetName(), nullptr);

    return entityPtr;
}

Entity* World::CreateEntity(Entity* root) { return CreateEntity("Entity_" + std::to_string(m_nextEntityId), root); }

Entity* World::CreateEntity(const std::string& name, Entity* root)
{
    auto* entityPtr = new Entity(this, m_nextEntityId++, name);

    m_entities.push_back(entityPtr);

    entityPtr->SetParent(root);

    return entityPtr;
}

red::Entity* World::CreateSingletonEntity()
{
    if (m_singletonEntity != nullptr)
        return m_singletonEntity;

    m_singletonEntity = CreateEntity("__SingletonEntity__", nullptr);

    m_singletonEntity->AddComponent<DebugComponent>();
    m_singletonEntity->AddComponent<UserInputComponent>();

    return m_singletonEntity;
}

void World::Init()
{
    CreateSingletonEntity();

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

void World::Clean()
{
    std::vector<Entity*> entitiesToRemove;
    for (auto* entity : m_entities)
    {
        if (entity->m_isDestroyed)
        {
            entitiesToRemove.push_back(entity);
            delete entity;
        }
    }

    for (auto* e : entitiesToRemove)
        m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), e), m_entities.end());
}

const std::vector<System*>& World::GetSystems() { return m_systems; }

const std::vector<Entity*>& World::GetEntities() { return m_entities; }

Entity* World::GetSingletonEntity() { return m_singletonEntity; }

ComponentManager* World::GetComponentManager() { return m_componentManager; }

PhysicsWorld* World::GetPhysicsWorld() { return &m_physicsWorld; }

}  // namespace red
