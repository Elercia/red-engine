#include "RedEngine/Core/Entity/World.hpp"

#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Level/LevelResourceLoader.hpp"
#include "RedEngine/Resources/ResourceHolderComponent.hpp"

#include <algorithm>
#include <cassert>

namespace red
{
World::World()
    : m_singletonEntity(nullptr)
    , m_componentManager(new ComponentManager())
    , m_componentRegistry(new ComponentRegistry())
    , m_nextEntityId(0)
    , m_currentLevel(nullptr)
{
}

World::~World()
{
    for (auto& system : m_systems)
    {
        delete system;
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

Entity* World::CreateEntity(Entity* root)
{
    return CreateEntity("Entity_" + std::to_string(m_nextEntityId), root);
}

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

    return m_singletonEntity;
}

void World::Init()
{
    std::sort(m_systems.begin(), m_systems.end(),
              [](const System* s1, const System* s2) { return s1->GetPriority() > s2->GetPriority(); });

    for (auto& system : m_systems)
    {
        if (!system->m_isInit)
            system->Init();
    }
}

void World::Finalize()
{
    ChangeLevel(nullptr);

    for (auto& entity : m_entities)
    {
        entity->Destroy();
    }

    for (auto& system : m_systems)
    {
        system->Finalise();
    }
}

bool World::Update()
{
    std::sort(m_systems.begin(), m_systems.end(),
              [](const System* s1, const System* s2) { return s1->GetPriority() > s2->GetPriority(); });

    EventsComponent* events = GetSingletonComponent<EventsComponent>();

    bool quit = events->QuitRequested();

    if (quit)
        return false;

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
        system->PostUpdate();
    }

    return true;
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

void World::LoadLevel(const std::string& levelName)
{
    auto* levelResourceLoader = GetSingletonComponent<ResourceHolderComponent>()->GetResourceLoader<LevelResourceLoader>();

    levelResourceLoader->LoadResource(levelName);
}

void World::ChangeLevel(Level* newLevel)
{
    if (m_currentLevel != nullptr)
    {
        m_currentLevel->InternFinalize();
        RED_SAFE_DELETE(m_currentLevel);
    }

    m_currentLevel = newLevel;

    if (m_currentLevel != nullptr)
        m_currentLevel->InternInit();

    for (auto* system : m_systems)
    {
        system->ManageEntities();
    }
}

const std::vector<System*>& World::GetSystems()
{
    return m_systems;
}

const std::vector<Entity*>& World::GetEntities()
{
    return m_entities;
}

Entity* World::GetSingletonEntity()
{
    return m_singletonEntity;
}

ComponentManager* World::GetComponentManager()
{
    return m_componentManager;
}


red::ComponentRegistry* World::GetComponentRegistry()
{
    return m_componentRegistry;
}

PhysicsWorld* World::GetPhysicsWorld()
{
    return &m_physicsWorld;
}


red::Level* World::GetCurrentLevel()
{
    return m_currentLevel;
}

}  // namespace red
