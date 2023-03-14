#pragma once

#include "RedEngine/Core/Container/Array.hpp"
#include "RedEngine/Core/Debug/Profiler.hpp"
#include "RedEngine/Core/Entity/Entity.hpp"
#include "RedEngine/Core/Memory/LinearAllocator.hpp"
#include "RedEngine/Math/Vector.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#include <algorithm>
#include <memory>
#include <tuple>

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

    virtual ArrayView<TypeTraits> GetROComponents() const = 0;
    virtual ArrayView<TypeTraits> GetRWComponents() const = 0;

protected:
    World* m_world;
    TypeTraits m_typeTraits;
};

struct BaseQuery
{
};

template <typename T>
struct QueryRO : public BaseQuery
{
    using ComponentType = T;

    bool IsReadOnly = true;
    TypeTraits GetTypeInfo() const;

    struct Result
    {
        using ComponentType = T;

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
struct QueryRW : public BaseQuery
{
    using ComponentType = T;

    bool IsReadOnly = false;

    TypeTraits GetTypeInfo() const;

    struct Result
    {
        using ComponentType = T;

        Result(T* ptr);

        bool operator==(const Result& other) const;

        T* Get();
        T* operator->();
        T* operator*();

    private:
        T* component;
    };
};

struct BaseQueryGroup
{
};

template <typename... Queries>
struct QueryGroup : public BaseQueryGroup
{
    static_assert(all_true<std::is_base_of_v<BaseQuery, Queries>...>::value,
                  "System created with something else than a Query type inside a QueryGroup");

    using ResultTuple = std::tuple<typename Queries::Result...>;
    using QueriesTuple = std::tuple<Queries...>;

    QueriesTuple queries;

    static const ResultTuple nulltuple;
};

template <typename Query>
struct SinglQuery : BaseQueryGroup
{
    static_assert(std::is_base_of_v<BaseQuery, Query>,
                  "System created with something else than a Query type inside a SinglQuery");

    using ResultType = typename Query::Result;
    using QueriesTuple = std::tuple<Query>;

    QueriesTuple queries;
};

template <typename... QueriesGroups>
class System : public BaseSystem
{
protected:
    typedef std::tuple<QueriesGroups...> PossibleQueries;

    static_assert(all_true<std::is_base_of_v<BaseQueryGroup, QueriesGroups>...>::value,
                  "System created with something else than a QueryGroup type");

public:
    System(World* world);
    ~System();

    template <int QueryGroupIndex>
    Array<typename std::tuple_element_t<QueryGroupIndex, std::tuple<QueriesGroups...>>::ResultTuple,
          DoubleLinearArrayAllocator>
    QueryComponents();

    template <int QueryGroupIndex>
    typename std::tuple_element_t<QueryGroupIndex, std::tuple<QueriesGroups...>>::ResultType QuerySingletonComponent();

    virtual ArrayView<TypeTraits> GetROComponents() const override;
    virtual ArrayView<TypeTraits> GetRWComponents() const override;

private:
    static consteval int GetROComponentCount();
    static consteval int GetRWComponentCount();

    TypeTraits* m_ROComponents; // Array of TypeTraits
    TypeTraits* m_RWComponents; // Array of TypeTraits
};

}  // namespace red

#include "inl/System.inl"
