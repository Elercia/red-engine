#include "RedEngine/Core/Entity/World.hpp"

#include "RedEngine/Core/CoreModule.hpp"

#include "RedEngine/Audio/System/AudioSystem.hpp"
#include "RedEngine/Core/Debug/Component/DebugComponent.hpp"
#include "RedEngine/Core/Debug/System/DebugSystem.hpp"
#include "RedEngine/Core/Entity/Components/ComponentManager.hpp"
#include "RedEngine/Core/Entity/Components/Transform.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Entity/System.hpp"
#include "RedEngine/Core/Entity/SystemExecutionGraph.hpp"
#include "RedEngine/Core/Event/Component/EventsComponent.hpp"
#include "RedEngine/Core/Event/System/EventSystem.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Input/System/UserInputSystem.hpp"
#include "RedEngine/Level/JsonLevelLoader.hpp"
#include "RedEngine/Level/Level.hpp"
#include "RedEngine/Physics/System/PhysicsSystem.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Rendering/System/SpriteAnimationSystem.hpp"
#include "RedEngine/Thread/ExecutionGraph.hpp"
#include "RedEngine/Utils/Random.hpp"

#include <algorithm>
#include <cassert>

namespace red
{
static int s_nameCounter = 0;

World::World()
    : m_entityAllocator(sizeof(Entity), 100)
    , m_componentManager(new ComponentManager(this))
    , m_componentRegistry(new ComponentRegistry())
    , m_currentLevel(nullptr)
    , m_levelLoader(nullptr)
{
    RegisterComponentType<Transform>();
}

World::~World()
{
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

    for (auto* child : entity->GetChildren())
    {
        OnAddEntity(child);
    }
}

void World::OnRemoveEntity(Entity* entity)
{
    auto it = std::find(m_entities.begin(), m_entities.end(), entity);

    if (it != m_entities.end())
        m_entities.erase(it);

    m_entityAllocator.Free(entity);
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
    RED_SAFE_DELETE(m_levelLoader);
    m_levelLoader = new JsonLevelLoader(this);
}

void World::InitSystems()
{
    for (auto* system : m_addedSystems)
    {
        system->Init();
    }

    m_addedSystems.clear();
}

void World::SetExecutionGraph(ExecutionGraph&& graph)
{
    m_executionGraph = std::move(graph);
}

void World::BuildExecutionGraph()
{
    m_executionGraph.New()
        .AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<BeginNextFrameRenderingSystem>().Build())
        .AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<EventSystem>().Build())
        .AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<UserInputSystem>().Build())
        .AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<PhysicSystem>().Build());

    if (m_currentLevel != nullptr)
        m_currentLevel->AddGameplaySystems(m_executionGraph);

#ifdef RED_DEVBUILD
    m_executionGraph.AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<DebugSystem>().Build());
#endif

    m_executionGraph
        .AddStage(SystemGraphStageBuilder::NewStage(this)
                      .AddSystem<SpriteAnimationSystem>()
                      .AddSystem<AudioSystem>()
                      .AddSystem<UpdateRenderableSystem>()
                      .Build())
        .AddStage(SystemGraphStageBuilder::NewStage(this).AddSystem<FlushRenderSystem>().Build());
}

void World::Finalize()
{
    // Delete current level entities
    ChangeLevel(nullptr);

    for (auto& system : m_systems)
    {
        system->Finalize();
        RED_SAFE_DELETE(system);
    }

    m_systems.clear();
    m_addedSystems.clear();

    Clean();

    RED_SAFE_DELETE(m_levelLoader);

    RED_SAFE_DELETE(m_componentManager);
    RED_SAFE_DELETE(m_componentRegistry);
}

bool World::Update()
{
    Clean();

    EventsComponent* events = GetWorldComponent<EventsComponent>();

    bool quit = events != nullptr ? events->QuitRequested() : false;

    if (quit)
        return false;

    for (auto* entity : m_entities)
    {
        auto* tranform = entity->GetComponent<Transform>();

        tranform->UpdateWorldMatrixIfNeeded();
    }

    m_executionGraph.Run();

    return true;
}

void World::Clean()
{
    if (m_currentLevel != nullptr)
        m_currentLevel->Clean();

    Array<Entity*> toRemove;
    for (auto* e : m_entities)
    {
        if (e->GetState() == EntityState::Destroyed)
        {
            toRemove.push_back(e);
        }
    }

    for (auto* e : toRemove)
    {
        OnRemoveEntity(e);
    }

    InitSystems();
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
    {
        RED_LOG_INFO("Change level {}", newLevel->GetName());

        m_currentLevel->InternInit();

        BuildExecutionGraph();
    }
}

const Array<BaseSystem*>& World::GetSystems() const
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
    Entity* e = m_entityAllocator.Allocate<Entity>(this, GetNewEntityId());

    e->SetName(name);
    e->SetParent(nullptr);

    OnAddEntity(e);

    return e;
}

Entity* World::CreateEntity(Entity* parent)
{
    Entity* e = m_entityAllocator.Allocate<Entity>(this, GetNewEntityId());

    e->SetName("Unnamed" + std::to_string(s_nameCounter++));
    e->SetParent(parent);

    OnAddEntity(e);

    return e;
}

Entity* World::CreateEntity(Entity* parent, EntityId id)
{
    if (FindEntity(id))
        return nullptr;

    Entity* e = m_entityAllocator.Allocate<Entity>(this, id);

    e->SetName("Unnamed" + std::to_string(s_nameCounter++));
    e->SetParent(parent);

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
    return (EntityId) RandomUint64();
}
}  // namespace red
