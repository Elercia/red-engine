#pragma once

#include "RedEngine/Core/Entity/World.hpp"
#include "RedEngine/RedEngineBase.hpp"
#include "RedEngine/Resources/Resource.hpp"
#include "RedEngine/Utils/Uncopyable.hpp"

#include <string>

namespace red
{
class Level : public IResource
{
public:
    enum class State
    {
        Loading,
        Ready
    };
    
    friend class ILevelSerializer;
    friend class JsonLevelSerializer;

    explicit Level(std::string name, World* world);
    virtual ~Level() = default;

    void InternInit();
    void InternFinalize();

    virtual void Init(){};
    virtual void Finalize(){};

    const std::string& GetName() const;

    Entity* CreateEntity();
    Entity* CreateEntity(EntityId id, const std::string& name);
    Entity* CreateEntity(EntityId id, const std::string& name, Entity* parent);
    Entity* CreateEntity(const std::string& name);
    Entity* CreateEntity(const std::string& name, Entity* parent);

    Entity* GetRootEntity();
    const Entity* GetRootEntity() const;

    void Serialize(const Path& path) const;

    void SetState(State state);

protected:
    std::string m_levelName;

    World* m_world;

    Entity* m_rootEntity;

    State m_state;
};
}  // namespace red
