#include "RedEngine/Core/Entity/World.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/JsonLevelLoader.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Level/LevelChunk.hpp"
#include "RedEngine/Utils/Random.hpp"

#include <algorithm>
#include <cassert>

namespace red
{
World::World()
    : m_worldChunk(nullptr)
    , m_componentManager(new ComponentManager(this))
    , m_componentRegistry(new ComponentRegistry())
    , m_currentLevel(nullptr)
    , m_levelLoader(nullptr)
{
    RegisterComponentType<Transform>();
}

World::~World()
{
    for (auto& system : m_systems)
    {
        system->Finalise();
        delete system;
    }

    m_systems.clear();

    m_worldChunk->Finalize();

    Clean();

    delete m_componentManager;
    delete m_worldChunk;
}

void World::OnAddEntity(Entity* entity)
{
    Entity* oldEntity = FindEntity(entity->GetId());
    if (oldEntity != nullptr)
    {
        RED_LOG_ERROR("Create a entity with a id that already exist (id: {}, name{})", entity->GetId(),
                      entity->GetName());
        return;
    }

    m_entities.push_back(entity);
}

void World::OnAddEntities(Array<Entity*>& entities)
{
    m_entities.insert(m_entities.end(), entities.begin(), entities.end());
}

void World::OnRemoveEntity(Entity* entity)
{
    auto it = std::find(m_entities.begin(), m_entities.end(), entity);

    if (it != m_entities.end())
        m_entities.erase(it);
}

void World::OnRemoveEntities(Array<Entity*>& entities)
{
    m_entities.erase(remove_if(m_entities.begin(), m_entities.end(),
                               [&](auto x) { return find(entities.begin(), entities.end(), x) != entities.end(); }),
                     m_entities.end());
}

Entity* World::FindEntity(EntityId id)
{
    for (Entity* e : m_entities)
    {
        if (e->GetId() == id)
            return e;
    }

    return nullptr;
}

void World::Init()
{
    m_worldChunk = new LevelChunk(this);
    m_worldChunk->Init();

    m_levelLoader = new JsonLevelLoader(this);
}


void World::InitSystems()
{
    std::sort(m_systems.begin(), m_systems.end(),
              [](const System* s1, const System* s2) { return s1->GetPriority() > s2->GetPriority(); });

    for (auto* system : m_systems)
    {
        if (!system->m_isInit)
            system->Init();
    }
}

void World::Finalize()
{
    ChangeLevel(nullptr);

    m_worldChunk->Finalize();

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
    Clean();

    EventsComponent* events = GetWorldComponent<EventsComponent>();

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
    if (m_currentLevel != nullptr)
        m_currentLevel->Clean();

    if (m_worldChunk != nullptr)
        m_worldChunk->Clean();

    InitSystems();
}

void World::AddGarbageEntityId(EntityId entityId)
{
    RED_ASSERT(std::find(m_entityIdGarbage.begin(), m_entityIdGarbage.end(), entityId) == m_entityIdGarbage.end(),
               "EntityId is already inside entity garbage, this may lead to 2 entities with the same ID");

    m_entityIdGarbage.push_back(entityId);
}

void World::LoadLevel(const Path& levelPath)
{
    Level* level = m_levelLoader->LoadLevel(levelPath);

    if (level != nullptr)
    {
        ChangeLevel(level);
    }
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

const Array<System*>& World::GetSystems() const
{
    return m_systems;
}

const Array<Entity*>& World::GetEntities() const
{
    return m_entities;
}

Array<Entity*>& World::GetEntities()
{
    return m_entities;
}

Entity* World::CreateWorldEntity(const std::string& name)
{
    Entity* e = m_worldChunk->CreateEntity(name);

    OnAddEntity(e);

    return e;
}

ComponentManager* World::GetComponentManager()
{
    return m_componentManager;
}

ComponentRegistry* World::GetComponentRegistry()
{
    return m_componentRegistry;
}

PhysicsWorld* World::GetPhysicsWorld()
{
    return &m_physicsWorld;
}

Level* World::GetCurrentLevel()
{
    return m_currentLevel;
}

EntityId World::GetNewEntityId()
{
    if (!m_entityIdGarbage.empty())
    {
        const auto id = m_entityIdGarbage.back();
        m_entityIdGarbage.pop_back();

        return id;
    }

    return (EntityId) RandomUint64();
}
}  // namespace red
