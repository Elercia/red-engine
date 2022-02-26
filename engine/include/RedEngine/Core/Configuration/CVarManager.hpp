#pragma once

#include "RedEngine/Core/Configuration/CVarUtils.hpp"
#include "RedEngine/Core/Container/Map.hpp"
#include "RedEngine/Filesystem/Path.hpp"
#include "RedEngine/Core/Debug/DebugMacros.hpp"
#include "RedEngine/Utils/TypesInfo.hpp"

#include <string>

namespace red
{
class ICVar;
template <typename Type>
class CVar;
template <typename Type>
class CVarValue;

class CVarManager
{
public:
    static CVarManager& GetInstance();

    template <typename T>
    static CVarValue<T>* NewConsoleVariableDeclaration(const std::string& name, const std::string& category,
                                              const T& defaultValue);

    static void LoadConfigFile(const Path& path);

public:
    CVarManager();
    ~CVarManager();

private:
    void LoadConfigFileInternal(const Path& path);

    template <typename T>
    CVarValue<T>* NewConsoleVariableDeclarationInternal(const std::string& name, const std::string& category,
                                                 const T& defaultValue);

    ICVar* FindCVar(const std::string& fullName);

    Map<std::string, ICVar*> m_configVariable;
};

}  // namespace red

#include "inl/CVarManager.inl"