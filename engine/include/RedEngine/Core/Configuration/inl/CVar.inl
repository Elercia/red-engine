namespace red
{
template <typename Type>
CVar<Type>::CVar(std::string name, Type defaultValue, std::string category)
    : ICVar(name, category)
    , m_defaultValue(defaultValue)
    , m_currentValue(defaultValue)
    , m_valueChangeCallback()
{
}

template <typename Type>
void CVar<Type>::ChangeValue(Type newValue)
{
    m_currentValue = newValue;

    m_valueChangeCallback(this);
}

template <typename Type>
void CVar<Type>::Reset()
{
    m_currentValue = m_defaultValue;

    m_valueChangeCallback(this);
}

template <typename Type>
Type CVar<Type>::GetValue()
{
    return m_currentValue;
}

template <typename Type>
void CVar<Type>::RegisterChangeCallback(std::function<void(CVar<Type>* variable)> callback)
{
    m_valueChangeCallback = callback;
}
}  // namespace red