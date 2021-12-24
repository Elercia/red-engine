#include "RedEngine/Level/LevelModule.hpp"
#include "RedEngine/Level/Level.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/JsonLevelSerializer.hpp"
#include "RedEngine/Level/LevelChunk.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <fstream>
#include <iosfwd>
#include <memory>

namespace red
{
Level::Level(std::string name, World* world) : m_levelName(std::move(name)), m_world(world), m_state(State::Created)
{
    m_mainLevelChunk = new LevelChunk(this);
}

void Level::InternInit()
{
    Init();

    m_mainLevelChunk->Init();

    m_state = State::Ready;
}

void Level::InternFinalize()
{
    Finalize();

    m_mainLevelChunk->Finalize();

    m_state = State::Finalized;
}

void Level::Clean()
{
    m_mainLevelChunk->Clean();
}

const std::string& Level::GetName() const
{
    return m_levelName;
}

World* Level::GetWorld()
{
    return m_world;
}

Entity* Level::GetRootEntity() const
{
    return m_mainLevelChunk->GetRootEntity();
}

Entity* Level::CreateEntity()
{
    Entity* e = m_mainLevelChunk->CreateEntity();

    OnEntityCreated(e);

    return e;
}

Entity* Level::CreateEntity(const std::string& name)
{
    Entity* e = m_mainLevelChunk->CreateEntity(name);

    OnEntityCreated(e);

    return e;
}

Entity* Level::CreateEntity(const std::string& name, Entity* parent)
{
    Entity* e = m_mainLevelChunk->CreateEntity(name, parent);

    OnEntityCreated(e);

    return e;
}

Entity* Level::CreateEntity(EntityId id, const std::string& name)
{
    Entity* e = m_mainLevelChunk->CreateEntity(id, name);

    OnEntityCreated(e);

    return e;
}

Entity* Level::CreateEntity(EntityId id, const std::string& name, Entity* parent)
{
    Entity* e = m_mainLevelChunk->CreateEntity(id, name, parent);

    OnEntityCreated(e);

    return e;
}

Array<Entity*>& Level::GetEntities()
{
    return m_mainLevelChunk->GetEntities();
}

const Array<Entity*>& Level::GetEntities() const
{
    return m_mainLevelChunk->GetEntities();
}

void Level::Serialize(const Path& path) const
{
    JsonLevelSerializer serializer(this);

    if (serializer.Serialize(path) == false)
        RED_LOG_ERROR("Failed to serialize level to \"{}\"", path.GetAscciiPath());
}

void Level::SetState(State state)
{
    m_state = state;
}

void Level::OnEntityCreated(Entity* e)
{
    if (m_state == State::Ready)
    {
        m_world->OnAddEntity(e);
    }
}
}  // namespace red