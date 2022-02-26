
#include "RedEngine/Core/SerializationFunction.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

namespace red
{
template <class Type>
CVar<Type>::CVar(std::string name, std::string category, Type defaultValue)
{
    CVarManager::NewConsoleVariableDeclaration(this, name, category, defaultValue);
}

template <class Type>
Type CVar<Type>::GetValue()
{
    Type e;
    
    if( !Deserialize(e, m_value->m_currentValue) )
    {
        RED_LOG_ERROR("Couldn't deserialize value {} into a {}", m_value->m_currentValue, TypeInfo<Type>().name);
    }

    return e;
}

template <class Type>
CVar<Type>::operator Type()
{
    return GetValue();
}

template <class Type>
CVarValue* CVar<Type>::operator->()
{
    return m_value;
}

template <class Type>
void CVar<Type>::ChangeValue(Type value)
{
    std::string stringValue = Serialize(value);
    m_value->ChangeValue(stringValue);
}
}  // namespace red