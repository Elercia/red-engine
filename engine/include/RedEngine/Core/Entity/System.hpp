#pragma once

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "World.hpp"

namespace red
{
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

    template <class... ComponentTypes>
    std::vector<Entity*> GetComponents();

protected:
    World* m_world;
};
}  // namespace red

#include "inl/System.inl"
