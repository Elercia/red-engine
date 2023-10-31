namespace red
{
template <typename... Args>
Delegate<Args...>::Delegate() : m_functions(), m_nextIndex(0)
{
}

template <typename... Args>
Delegate<Args...>::~Delegate()
{
}

template <typename... Args>
void Delegate<Args...>::operator()(Args... args)
{
    for (auto& pair : m_functions)
    {
        pair.second(std::forward<Args>(args)...);
    }
}

template <typename... Args>
typename Delegate<Args...>::FuncIndex Delegate<Args...>::Add(typename Delegate<Args...>::FuncType func)
{
    FuncIndex index = m_nextIndex;
    m_nextIndex++;

    m_functions.insert({index, std::move(func)});

    return index;
}

template <typename... Args>
void Delegate<Args...>::Remove(typename Delegate<Args...>::FuncIndex index)
{
    if (index != (FuncIndex)-1)
    {
        m_functions.erase(index);
    }
}
}  // namespace red
