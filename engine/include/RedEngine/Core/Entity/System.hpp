#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#include <algorithm>
#include <memory>

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
    virtual void EndRender(){};

    /// Called once the world is initializing to manager system-specific init
    virtual void Init();

    /// Called once the system is shutting down to manage system-specific shutdown
    virtual void Finalise();

    // TODO Create the same inside world (fallback call to world)
    template <class... ComponentTypes>
    Array<Entity*, red::DoubleLinearArrayAllocator> GetComponents() const;

    // Utilities functions
    void DebugDrawLine(const Vector2& from, const Vector2& to);

    void SetTypeTraits(TypeTraits typeTraits);
    std::size_t GetTypeId() const;

    int GetPriority() const;

    Array<Entity*>& GetWorldEntities();
    const Array<Entity*>& GetWorldEntities() const;

protected:
    bool m_isInit;
    World* m_world;
    int m_priority;
    TypeTraits m_typeTraits;
};
}  // namespace red

#include "inl/System.inl"
