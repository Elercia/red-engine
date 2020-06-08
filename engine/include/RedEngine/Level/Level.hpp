#pragma once

#include <memory>

#include <RedEngine/Utils/Uncopyable.hpp>
#include <RedEngine/Core/Entity/World.hpp>

namespace red
{
class Level : public Uncopyable
{
public:
    explicit Level(const char* name);
    virtual ~Level() = default;

    virtual void Init(World& world) = 0;
    virtual void Finalize(World& world) = 0;

protected:
    const char* m_levelName;
};
}  // namespace red
