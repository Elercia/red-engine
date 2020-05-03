namespace red
{
template <class Type>
CVar<Type>::CVar(std::string name, std::string category, Type defaultValue)
{
    Configuration::NewConsoleVariableDeclaration(this, name, category, defaultValue);
}

template <class Type>
Type CVar<Type>::GetValue()
{
    static_assert(has_serialization_overload<Type>::value,
                  "No deserialization function provided for console type T");

    Type e;
    red_deserialize_configuration_type(m_value->m_currentValue, e);

    return e;
}

template <class Type>
CVarValue* CVar<Type>::operator->()
{
    return m_value;
}
}  // namespace red