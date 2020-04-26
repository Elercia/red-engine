#pragma once

#include <memory>

#include <RedEngine/Utils/Uncopyable.hpp>

namespace red
{
class World;

class Level : public Uncopyable
{
public:
    explicit Level(const char* name);
    virtual ~Level() = default;

    virtual void Init() = 0;
    virtual void Finalize() = 0;

    void Update();

    void CreateWorld(bool registerDefaultSystems = true);

protected:
    const char* m_levelName;

    std::unique_ptr<World> m_world;
};
}  // namespace red
