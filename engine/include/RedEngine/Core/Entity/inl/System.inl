#include "System.hpp"
namespace red
{
template <typename T>
inline QueryRO<T>::Result::Result(T* ptr) : component(ptr)
{
}

template <typename T>
inline bool QueryRO<T>::Result::operator==(const Result& other) const
{
    return component == other.component;
}

template <typename T>
inline const T* QueryRO<T>::Result::Get()
{
    return component;
}

template <typename T>
inline const T* QueryRO<T>::Result::operator->()
{
    return component;
}

template <typename T>
inline const T* QueryRO<T>::Result::operator*()
{
    return component;
}

template <typename T>
inline QueryRW<T>::Result::Result(T* ptr) : component(ptr)
{
}

template <typename T>
inline bool QueryRW<T>::Result::operator==(const Result& other) const
{
    return component == other.component;
}

template <typename T>
inline T* QueryRW<T>::Result::Get()
{
    return component;
}

template <typename T>
inline T* QueryRW<T>::Result::operator->()
{
    return component;
}

template <typename T>
inline T* QueryRW<T>::Result::operator*()
{
    return component;
}

template <typename... QueriesT>
inline System<QueriesT...>::System(World* world) : BaseSystem(world)
{
}

template <typename... QueriesT>
Array<std::tuple<Entity*, typename QueriesT::Result...>, DoubleLinearArrayAllocator>
System<QueriesT...>::QueryComponents()
{
    PROFILER_EVENT_CATEGORY("System::GetComponents", ProfilerCategory::None)

    // TODO Fist element should be the entity ? Why ? 
    Array<std::tuple<Entity*, typename QueriesT::Result...>, DoubleLinearArrayAllocator> selectedEntities;

    auto nullTuple = std::make_tuple((Entity*) nullptr, typename QueriesT::Result(nullptr)...);
    auto& worldentities = GetEntities();
    for (auto& entityPtr : worldentities)
    {
        auto tuple = std::make_tuple(
            entityPtr, typename QueriesT::Result(entityPtr->GetComponent<typename QueriesT::ComponentType>())...);

        if (tuple != nullTuple)
            selectedEntities.push_back(tuple);
    }

    return selectedEntities;
}

}  // namespace red