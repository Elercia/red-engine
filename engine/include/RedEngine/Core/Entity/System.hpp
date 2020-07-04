#pragma once

#include <memory>
#include <vector>
#include <RedEngine/Math/Vector.hpp>

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
    virtual void FixedUpdate(){};
    virtual void Update(){};
    virtual void PreUpdate(){};
    virtual void LateUpdate(){};

    /// Called once the world is initializing to manager system-specific init
    virtual void Init(){};
    /// Called once the system is shutting down to manage system-specific shutdown
    virtual void Finalise(){};

    template <class... ComponentTypes>
    std::vector<Entity*> GetComponents();

    Entity& GetSingletonEntity();

    // Utilities functions
    void DebugDrawLine(const Vector2& from, const Vector2& to);

protected:
    World* m_world;
};
}  // namespace red

#include "inl/System.inl"
