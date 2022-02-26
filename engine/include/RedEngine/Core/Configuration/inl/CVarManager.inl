
#include "RedEngine/Core/SerializationFunction.hpp"
namespace red
{
template <typename T>
void CVarManager::NewConsoleVariableDeclaration(CVar<T>* cvar, const std::string& name, const std::string& category,
                                                T defaultValue)
{
    std::string stringValue = Serialize(defaultValue);

    auto* cVarValue = CVarManager::NewConsoleVariableDeclaration(name, category, stringValue);
    cvar->m_value = cVarValue;
}
}  // namespace red