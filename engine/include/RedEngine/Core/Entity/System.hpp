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

    // Update functions called in this order
    virtual void FixedUpdate(float fixedDeltaTime){};
    virtual void Update(float deltaTime) = 0;
    virtual void PreUpdate(float deltaTime){};
    virtual void LateUpdate(float deltaTime){};

    // Call once the system is shutting down to manage system-specific shutdown
    virtual void Finalise(){};

    template <class... ComponentTypes>
    std::vector<Entity*> GetComponents();

protected:
    World* m_world;
};
}  // namespace red

#include "inl/System.inl"
