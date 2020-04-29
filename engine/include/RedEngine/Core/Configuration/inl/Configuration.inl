#include "../ConfigurationUtils.hpp"

namespace red
{
template <typename T>
void Configuration::ChangeVar(std::string name, std::string category, T value)
{
    auto it = m_configVariable.find(category + "_" + name);

    if (it == m_configVariable.end())
    {
        return;
    }

    auto casted = static_cast<CVarValue<T>*>(it->second);

    casted->ChangeValue(value);
}

template <class Type>
void Configuration::NewCVar(CVar<Type>* cvar, std::string name, Type defaultValue,
                            std::string category)
{
    auto* cVarValue = GetInstance().RegisterNewConfigVariable(name, defaultValue, category);

    cvar->m_value = cVarValue;
}

template <class Type>
CVarValue<Type>* Configuration::RegisterNewConfigVariable(const std::string& name,
                                                          Type defaultValue,
                                                          const std::string& category)
{
    auto it = m_configVariable.find(ConfigurationUtils::GetLongName(category, name));
    if (it == m_configVariable.end())
    {
        auto* cVarValue = new CVarValue<Type>{name, defaultValue, category};
        m_configVariable.insert({ConfigurationUtils::GetLongName(category, name), cVarValue});
        return cVarValue;
    }
    else
    {
        return static_cast<CVarValue<Type>*>(it->second);
    }
}
}  // namespace red