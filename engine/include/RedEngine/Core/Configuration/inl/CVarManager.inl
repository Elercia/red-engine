#include <fmt/format.h>

namespace red
{
template <typename T>
CVarValue<T>* CVarManager::NewConsoleVariableDeclaration(const String& name, const String& category,
                                                         const T& defaultValue)
{
    auto& instance = CVarManager::GetInstance();

    return instance.NewConsoleVariableDeclarationInternal(name, category, defaultValue);
}

template <typename T>
CVar<T> CVarManager::GetFromName(const String& fullName)
{
    return CVar<T>((CVarValue<T>*)FindCVar(fullName));
}

template <typename T>
CVarValue<T>* CVarManager::NewConsoleVariableDeclarationInternal(const String& name, const String& category,
                                                                 const T& defaultValue)
{
    auto fullName = CVarUtils::GetLongName(category, name);

    ICVar* cvarInterface = FindCVar(fullName);
    if (cvarInterface == nullptr)
    {
        cvarInterface = new CVarValue<T>(name, category, defaultValue);
        m_configVariable.insert({fullName, cvarInterface});
    }

    return (CVarValue<T>*) cvarInterface;
}
}  // namespace red