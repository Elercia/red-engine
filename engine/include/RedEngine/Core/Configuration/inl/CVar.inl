
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

namespace red
{
////////////////////////////////////////////////
//////// CVar
////////////////////////////////////////////////
template <class T>
CVar<T>::CVar(const std::string& name, const std::string& category, const T& defaultValue)
{
    m_value = CVarManager::NewConsoleVariableDeclaration(name, category, defaultValue);
}

template <class T>
T& CVar<T>::GetValue()
{
    return m_value->m_currentValue;
}

template <class T>
CVar<T>::operator T()
{
    return GetValue();
}

template <class T>
CVarValue<T>* CVar<T>::operator->()
{
    return m_value;
}

template <class T>
void CVar<T>::ChangeValue(const T& value)
{
    m_value->m_currentValue = value;
}

////////////////////////////////////////////////
//////// CVarValue
////////////////////////////////////////////////
template <class T>
CVarValue<T>::CVarValue(const std::string& name, const std::string& category, const T& defaultValue) : ICVar(name, category, TypeInfo<T>().typeId)
    , m_defaultValue(defaultValue) 
    , m_currentValue(defaultValue)
{
    m_deserializationFunction = [this](const std::string& strValue){
        return Deserialize(m_currentValue, strValue);
    };
}

template <class T>
void CVarValue<T>::ChangeValue(const T& newValue)
{
    m_currentValue = newValue;

    m_changeDelegate(this);
}

template <class T>
void CVarValue<T>::Reset()
{
    ChangeValue(m_defaultValue);
}

template <class T>
typename CVarValue<T>::ValueChangeDelegate::FuncIndex CVarValue<T>::OnValueChange(typename CVarValue<T>::ValueChangeDelegate::FuncType callback)
{
    return m_changeDelegate.Add(callback);
}
}  // namespace red