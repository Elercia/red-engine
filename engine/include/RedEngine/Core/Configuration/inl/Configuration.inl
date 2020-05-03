#include "../ConfigurationUtils.hpp"

namespace red
{
template <typename T>
void Configuration::NewConsoleVariableDeclaration(CVar<T>* cvar, std::string name,
                                                  std::string category, T defaultValue)
{
    static_assert(has_serialization_overload<T>::value,
                  "No serialization function provided for console type T");

    std::string stringValue = red_serialize_configuration_type(defaultValue);

    auto* cVarValue = Configuration::NewConsoleVariableDeclaration(name, category, stringValue);
    cvar->m_value = cVarValue;
}
}  // namespace red