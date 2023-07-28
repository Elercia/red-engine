#include "RedEngine/Level/Level.hpp"

#include "RedEngine/Level/LevelModule.hpp"

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Core/Memory/Macros.hpp"
#include "RedEngine/Input/Component/UserInput.hpp"
#include "RedEngine/Level/JsonLevelSerializer.hpp"
#include "RedEngine/Rendering/System/RenderingSystem.hpp"
#include "RedEngine/Resources/Resource.hpp"

#include <fstream>
#include <iosfwd>
#include <memory>

namespace red
{
Level::Level(String name, World* world)
    : m_rootEntity(nullptr), m_levelName(std::move(name)), m_world(world), m_state(State::Created)
{
}

Level::~Level()
{
}

void Level::InternInit()
{
    m_rootEntity = CreateEntity("Root", nullptr);

    Init();

    m_state = State::Ready;
}

void Level::InternFinalize()
{
    Finalize();

    m_rootEntity->Destroy();

    m_world->Clean();

    m_state = State::Finalized;
}

void Level::Clean()
{
}

const String& Level::GetName() const
{
    return m_levelName;
}

World* Level::GetWorld()
{
    return m_world;
}

Entity* Level::GetRootEntity() const
{
    return m_rootEntity;
}

Entity* Level::CreateEntity()
{
    Entity* e = m_world->CreateEntity(GetRootEntity());
    return e;
}

Entity* Level::CreateEntity(const String& name)
{
    Entity* e = m_world->CreateEntity(GetRootEntity());

    e->SetName(name);

    return e;
}

Entity* Level::CreateEntity(const String& name, Entity* parent)
{
    Entity* e = m_world->CreateEntity(GetRootEntity());

    e->SetName(name);
    e->SetParent(parent);

    return e;
}

Entity* Level::CreateEntity(EntityId id, const String& name)
{
    Entity* e = m_world->CreateEntity(GetRootEntity(), id);

    e->SetName(name);
    e->SetParent(GetRootEntity());

    return e;
}

Entity* Level::CreateEntity(EntityId id, const String& name, Entity* parent)
{
    Entity* e = m_world->CreateEntity(GetRootEntity(), id);

    e->SetName(name);
    e->SetParent(parent);

    return e;
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
}  // namespace red