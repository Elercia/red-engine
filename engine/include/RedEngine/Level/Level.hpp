#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include "RedEngine/Core/Container/String.hpp"

namespace red
{
class ExecutionGraph;

class Level : Uncopyable
{
public:
    enum class State
    {
        Created,
        Loading,
        Ready,
        Finalized
    };

    friend class ILevelSerializer;
    friend class JsonLevelSerializer;

    explicit Level(String name, World* world);
    virtual ~Level();

    void InternInit();
    void InternFinalize();

    virtual void Init(){};
    virtual void Finalize(){};

    virtual void AddGameplaySystems(ExecutionGraph& /*graph*/){};

    void Clean();

    const String& GetName() const;
    World* GetWorld();

    Entity* GetRootEntity() const;

    Entity* CreateEntity();
    Entity* CreateEntity(EntityId id, const String& name);
    Entity* CreateEntity(EntityId id, const String& name, Entity* parent);
    Entity* CreateEntity(const String& name);
    Entity* CreateEntity(const String& name, Entity* parent);

    void Serialize(const Path& path) const;

    void SetState(State state);

protected:
    Entity* m_rootEntity;
    String m_levelName;

    World* m_world;

    State m_state;
};
}  // namespace red
