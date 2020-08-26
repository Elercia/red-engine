#pragma once

#include <RedEngine/Utils/Uncopyable.hpp>
#include <RedEngine/Core/Entity/World.hpp>

#include <string>

namespace red
{
class Level : public Uncopyable
{
public:
    explicit Level(std::string name, World* world);
    virtual ~Level() = default;

    void InternInit();
    void InternFinalize();

    virtual void Init() = 0;
    virtual void Finalize() = 0;

    const std::string& GetName() const;

    Entity* CreateEntity();
    Entity* CreateEntity(const std::string& name);

    Entity* GetRootEntity();

protected:
    std::string m_levelName;

    World* m_world;

    Entity* m_rootEntity;
};
}  // namespace red
