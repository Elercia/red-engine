#pragma once

#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Math/Vector.hpp"

#include <algorithm>
#include <memory>
#include <vector>

namespace red
{
class World;

class System
{
    friend World;

public:
    System(World* world);
    System(System&&) = default;
    System(const System&) = delete;
    virtual ~System() = default;

    System& operator=(const System&) = delete;
    System& operator=(System&&) = default;

    // Update functions called in this order
    virtual void PreUpdate(){};
    virtual void Update(){};
    virtual void PostUpdate(){};

    virtual void BeginRender(){};
    virtual void Render(){};
    virtual void EndRender(){};

    /// Called once the world is initializing to manager system-specific init
    virtual void Init()
    {
        m_isInit = true;
    }

    /// Called once the system is shutting down to manage system-specific shutdown
    virtual void Finalise(){};

    virtual void ManageEntities(){};

    // TODO Create the same inside world (fallback call to world)
    template <class... ComponentTypes>
    std::vector<Entity*> GetComponents();

    // Utilities functions
    void DebugDrawLine(const Vector2& from, const Vector2& to);

    void SetTypeId(std::size_t typeId);
    std::size_t GetTypeId();

    int GetPriority() const;

    std::vector<Entity*> GetWorldEntities();

protected:
    bool m_isInit;
    World* m_world;
    int m_priority;
    std::size_t m_typeId;
};
}  // namespace red

#include "inl/System.inl"
