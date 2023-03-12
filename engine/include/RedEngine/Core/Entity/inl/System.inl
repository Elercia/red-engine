namespace red
{
template <typename... Queries>
const typename QueryGroup<Queries...>::ResultTuple QueryGroup<Queries...>::nulltuple =
    typename QueryGroup<Queries...>::ResultTuple(typename Queries::Result(nullptr)...);

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

template <typename... QueryResultType>
void FetchComponentTuple(std::tuple<QueryResultType...>& tuple, Entity* entityPtr)
{
    tuple = std::make_tuple<QueryResultType...>(
        QueryResultType(entityPtr->GetComponent<typename QueryResultType::ComponentType>())...);
}

template <typename... QueryResultType>
bool IsValidComponentTuple(std::tuple<QueryResultType...>& tuple)
{
    constexpr auto size = sizeof...(QueryResultType);
    bool present[] = {std::get<QueryResultType>(tuple).Get() != nullptr...};
    bool add = true;

    for (int i = 0; i != size; i++)
    {
        if (!present[i])
        {
            add = false;
            break;
        }
    }

    return add;
}

template <typename... QueriesGroups>
template <int QueryGroupIndex>
Array<typename std::tuple_element_t<QueryGroupIndex, std::tuple<QueriesGroups...>>::ResultTuple,
      DoubleLinearArrayAllocator>
System<QueriesGroups...>::QueryComponents()
{
    PROFILER_EVENT_CATEGORY("System::GetComponents", ProfilerCategory::None)

    static_assert(
        QueryGroupIndex >= 0 && QueryGroupIndex < std::tuple_size_v<typename System<QueriesGroups...>::PossibleQueries>,
        "Query index out of bound");

    using QueryType = std::tuple_element_t<QueryGroupIndex, typename System<QueriesGroups...>::PossibleQueries>;
    using ResultTupleType = QueryType::ResultTuple;

    Array<ResultTupleType, DoubleLinearArrayAllocator> selectedEntities;

    auto& worldentities = GetEntities();
    for (auto& entityPtr : worldentities)
    {
        ResultTupleType tuple = QueryType::nulltuple;
        FetchComponentTuple(tuple, entityPtr);

        if (IsValidComponentTuple(tuple))
            selectedEntities.push_back(tuple);
    }

    return selectedEntities;
}

template <typename... QueriesGroups>
template <int QueryGroupIndex>
typename std::tuple_element_t<QueryGroupIndex, std::tuple<QueriesGroups...>>::ResultType
System<QueriesGroups...>::QuerySingletonComponent()
{
    PROFILER_EVENT_CATEGORY("System::GetSingletonComponent", ProfilerCategory::None)

    static_assert(
        QueryGroupIndex >= 0 && QueryGroupIndex < std::tuple_size_v<typename System<QueriesGroups...>::PossibleQueries>,
        "Query index out of bound");

    using QueryType = std::tuple_element_t<QueryGroupIndex, typename System<QueriesGroups...>::PossibleQueries>;
    using ResultType = QueryType::ResultType;

    auto& worldentities = GetEntities();
    for (auto& entityPtr : worldentities)
    {
        auto comp = entityPtr->GetComponent<typename ResultType::ComponentType>();

        if (comp != nullptr)
            return ResultType(comp);
    }

    return ResultType(nullptr);
}

}  // namespace red