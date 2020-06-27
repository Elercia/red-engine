#pragma once

#include <memory>

#include <RedEngine/Utils/Uncopyable.hpp>
#include <RedEngine/Core/Entity/World.hpp>

namespace red
{
class Level : public Uncopyable
{
public:
    explicit Level(const char* name, World* world = nullptr);
    virtual ~Level() = default;

    virtual void Init() = 0;
    virtual void Finalize() = 0;

    void SetWorld(World* world);

protected:
    const char* m_levelName;
    World* m_world;
};
}  // namespace red
