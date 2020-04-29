
#include <sstream>

namespace red
{
template <typename Type>
CVarValue<Type>::CVarValue(std::string name, Type defaultValue, std::string category)
    : ICVarValue(name, category)
    , m_defaultValue(defaultValue)
    , m_currentValue(defaultValue)
    , m_valueChangeCallback()
{
}

template <typename Type>
void CVarValue<Type>::ChangeValue(Type newValue)
{
    m_currentValue = newValue;

    m_valueChangeCallback(this);
}

template <typename Type>
void CVarValue<Type>::Reset()
{
    m_currentValue = m_defaultValue;

    m_valueChangeCallback(this);
}

template <typename Type>
Type CVarValue<Type>::GetValue()
{
    return m_currentValue;
}

template <typename Type>
void CVarValue<Type>::RegisterChangeCallback(
    std::function<void(CVarValue<Type>* variable)> callback)
{
    m_valueChangeCallback = callback;
}

template <typename Type>
void CVarValue<Type>::ChangeValueString(std::string newValueStr)
{
    std::istringstream iss(newValueStr);
    iss >> m_currentValue;
}

template <class Type>
CVar<Type>::CVar(std::string name, Type defaultValue, std::string category)
{
    Configuration::NewCVar(this, name, defaultValue, category);
}

template <class Type>
Type CVar<Type>::GetValue()
{
    return m_value->GetValue();
}

template <class Type>
void CVar<Type>::ChangeValueString(std::string newValueStr)
{
    m_value->ChangeValueString(newValueStr);
}

template <class Type>
void CVar<Type>::ChangeValue(Type newValue)
{
    m_value->ChangeValue(newValue);
}

template <class Type>
void CVar<Type>::Reset()
{
    m_value->Reset();
}

template <class Type>
void CVar<Type>::RegisterChangeCallback(std::function<void(CVarValue<Type>*)> callback)
{
    m_value->RegisterChangeCallback(callback);
}
}  // namespace red