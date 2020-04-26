#pragma once

#include <RedEngine/Utils/Uncopyable.hpp>

namespace red
{
class World;

class Level : public Uncopyable
{
public:
    Level(const char* name);
    virtual ~Level() = default;

    virtual void Init(World* world) = 0;
    virtual void Finalize() = 0;

private:
    const char* m_levelName;
};
}  // namespace red
