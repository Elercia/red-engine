#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#include <algorithm>
#include <memory>

namespace red
{
class World;

class BaseSystem : private Uncopyable
{
    friend World;

public:
    BaseSystem(World* world);
    virtual ~BaseSystem() = default;

    virtual void Update() = 0;

    virtual void Init()
    {
    }
    virtual void Finalize()
    {
    }

    TypeTraits GetTypeTraits() const;

    Array<Entity*>& GetEntities();
    void SetTraits(TypeTraits typeTraits);

protected:
    World* m_world;
    TypeTraits m_typeTraits;
};

template <typename T>
struct QueryRO
{
    using ComponentType = T;

    struct Result
    {
        Result(T* ptr);

        bool operator==(const Result& other) const;

        const T* Get();
        const T* operator->();
        const T* operator*();

    private:
        const T* component;
    };
};

template <typename T>
struct QueryRW
{
    using ComponentType = T;

    struct Result
    {
        Result(T* ptr);

        bool operator==(const Result& other) const;

        T* Get();
        T* operator->();
        T* operator*();

    private:
        T* component;
    };
};

template <typename... QueriesT>
class System : public BaseSystem
{
public:
    System(World* world);

    Array<std::tuple<Entity*, typename QueriesT::Result...>, DoubleLinearArrayAllocator> QueryComponents();
};

}  // namespace red

#include "inl/System.inl"
