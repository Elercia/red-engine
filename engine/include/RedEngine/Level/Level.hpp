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
    friend class ILevelSerializer;
    friend class JsonLevelSerializer;

    RED_RESOURCE(ResourceType::LEVEL)

    explicit Level(std::string name, World* world);
    virtual ~Level() = default;

    void InternInit();
    void InternFinalize();

    virtual void Init() = 0;
    virtual void Finalize() = 0;

    const std::string& GetName() const;

    Entity* CreateEntity();
    Entity* CreateEntity(EntityId id, const std::string& name);
    Entity* CreateEntity(EntityId id, const std::string& name, Entity* parent);
    Entity* CreateEntity(const std::string& name);

    Entity* GetRootEntity();

    void Serialize(const std::string& path);
    void Deserialize(const std::string& path);

protected:
    std::string m_levelName;

    World* m_world;

    Entity* m_rootEntity;
};
}  // namespace red
