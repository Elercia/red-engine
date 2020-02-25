#pragma once

#include <memory>
#include <vector>
#include "Entity.hpp"

namespace red
{
class World;

class System
{
public:
    System(World* world);
    System(System&&) = default;
    System(const System&) = delete;
    virtual ~System() = default;

    System& operator=(const System&) = delete;
    System& operator=(System&&) = default;

    virtual void Update(float deltaTime) = 0;

    template <class ... ComponentTypes>
    std::vector<std::shared_ptr<Entity>> GetComponents();

protected:
    World* m_world;
};
}  // namespace red

#include "inl/System.inl"
