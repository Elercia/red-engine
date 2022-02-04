#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>

namespace red
{
class LevelChunk;

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

    explicit Level(std::string name, World* world);
    virtual ~Level();

    void InternInit();
    void InternFinalize();

    virtual void Init(){};
    virtual void Finalize(){};

    void Clean();

    const std::string& GetName() const;
    World* GetWorld();

    Entity* GetRootEntity() const;

    Entity* CreateEntity();
    Entity* CreateEntity(EntityId id, const std::string& name);
    Entity* CreateEntity(EntityId id, const std::string& name, Entity* parent);
    Entity* CreateEntity(const std::string& name);
    Entity* CreateEntity(const std::string& name, Entity* parent);

    Array<Entity*>& GetEntities();
    const Array<Entity*>& GetEntities() const;

    void Serialize(const Path& path) const;

    void SetState(State state);

private:
    void OnEntityCreated(Entity* e);

protected:
    std::string m_levelName;

    LevelChunk* m_mainLevelChunk;

    World* m_world;

    State m_state;
};
}  // namespace red
